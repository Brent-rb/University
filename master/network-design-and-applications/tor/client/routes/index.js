const fs = require("fs")
const NodeRSA = require("node-rsa")
const superagent = require("superagent")
const querystring = require("querystring")
const urlLib = require("url")
const multer = require("multer")
const PATH_LENGTH = 5

var express = require("express")
var router = express.Router()

var publicKeyFormat = "pkcs8-public-pem"

var directoryIP = "localhost:3000"
var directoryPath = "/nodes"
var directoryListPath = "/list"

var nodes = []

router.use(function timeLog(req, res, next) {
	//console.log("Time: ", Date.now())
	next()
})

router.all("/getResource", multer().any(), function(req, res) {
	var method = req.method.toLocaleLowerCase()
	// Build payload for last node
	var payload = buildLastPayload(method, req)
	console.log("Requested URL: %s, method: %s", payload.destination, payload.method)

	// Generate a path of nodes for this request
	var path = generatePath()
	console.log("Path: ")
	for(var index in path) {
		var node = path[index]
		console.log("\t%s:%d", node.host, node.port)
	}
	
	// Build the encrypted onion for this path
	payload = buildEncryptedPayload(path, payload)

	// Send the onion to the first node
	superagent.get(path[0].host + ":" + path[0].port)
	.query({
		payload: payload
	})
	.end((err, forwardedRes) => {
		try {
			decryptResult(path, res, forwardedRes)
		}
		catch(error) {
			console.log("Failed to decrypt answer.")
			console.log(error)
			res.sendStatus(404)
		}
	})
})

function decryptResult(path, res, forwardedRes) {
	var decrypted = forwardedRes.body.payload

	for(var index = 0; index < path.length; index++) {
		var node = path[index]
		var key = new NodeRSA()
		key.importKey(node.publicKey, publicKeyFormat)
		decrypted = key.decryptPublic(decrypted, "utf8")
	}
	
	var object = JSON.parse(decrypted)

	tryRes(res, "cookie", object, "cookie")
	tryRes(res, "location", object, "location")
	// This bugs because of headers already sent
	tryRes(res, "links", object, "links")
	tryRes(res, "type", object, "type")
	tryResDictionary(res, "set", object, "headers")
	// This bugs out because headers are already sent
	//tryRes(res, "sendStatus", object, "statusCode")
	tryResArray(res, "redirect", object, "redirects")

	var toSend = object.text
	if(!(toSend) || toSend == "") {
		if(object.body.hasOwnProperty("type") && object.body.type == "Buffer") {
			toSend = new Buffer(object.body)
		}
		else {
			toSend = object.body
		}
	}
	try {
		res.send(toSend)
	}
	catch(error) {
		console.log("Failed to send answer")
		console.log(error)
	}
}

// These functions try to set the properties we got as reply on the last node but they are not translatable 1-to-1 so we try
function tryRes(res, resFunction, object, objectAttribute) {
	try {
		if (object.hasOwnProperty(objectAttribute))
			res[resFunction](object[objectAttribute])
	}
	catch(e) {
		console.log("Failed to execute %s", resFunction)
		console.log(e)
	}
}

function tryResArray(res, resFunction, object, objectAttribute) {
	try {
		if (object.hasOwnProperty(objectAttribute)) {
			var array = object[objectAttribute]
			for (var index = 0; index < array.length; index++) {
				res[resFunction](array[index])
			}
		}	
	} catch (e) {
		console.log("Failed to execute %s", resFunction)
		console.log(e)
	}
}

function tryResDictionary(res, resFunction, object, objectAttribute) {
	try {
		if (object.hasOwnProperty(objectAttribute)) {
			var dictionary = object[objectAttribute]

			Object.keys(dictionary).forEach(function (key) {
				if (key.toLowerCase() != "content-encoding") {
					var value = dictionary[key]
					res[resFunction](key, value)
				}
			})
		}	
	} catch (e) {
		console.log("Failed to execute %s", resFunction)
		console.log(e)
	}
}

// Build payload for the last node, this payload includes all the necessary data to make the web request
function buildLastPayload(method, req) {
	var url = req.query.url || req.query.URL
	url = querystring.unescape(url)
	var queries = urlLib.parse(url, true).query
	
	var headers = Object.assign({}, req.headers)
	var body = Object.assign({}, req.body)
	var parsedURL = urlLib.parse(url, true)
	var hostName = ( parsedURL.host ? parsedURL.host : parsedURL.pathname )
	var files = req.files

	headers["host"] = hostName

	var payload = {
		method: method,
		destination: url,
		headers: headers,
		files: files
	}

	if(body)
		payload.body = body
	if(queries)
		payload.queries = queries

	return payload
}

// Based on a path of nodes, make an encrypted onion to send
function buildEncryptedPayload(path, payload) {
	var previousNodeLoad
	var previousNode

	for(var index = path.length - 1; index >= 0; index--) {
		var node = path[index]
		var key = new NodeRSA()
		key.importKey(node.publicKey, publicKeyFormat)

		if(index == path.length - 1) {
			previousNodeLoad = createFetchEvent(key, payload)
		}
		else {
			previousNodeLoad = createRelayEvent(previousNode, key, previousNodeLoad)
		}

		previousNode = node
	}

	return previousNodeLoad
}

function createFetchEvent(key, payload) {
	return key.encrypt(JSON.stringify({
		event: "fetch",
		payload: payload
	}), "base64")
}

function createRelayEvent(node, key, payload) {
	return key.encrypt(JSON.stringify({
		event: "relay",
		payload: {
			destination: node.host + ":" + node.port,
			payload: payload
		}
	}), "base64")
}

// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/random
function getRandomInt(min, max) {
	min = Math.ceil(min);
	max = Math.floor(max);
	return Math.floor(Math.random() * (max - min)) + min; //The maximum is exclusive and the minimum is inclusive
}

function generatePath() {
	var nodesToSearch = PATH_LENGTH + (getRandomInt(0, 3) - 1)
	var path = []
	var nodesCopy = nodes.slice()

	while(nodesToSearch > 0 && nodesCopy.length > 0) {
		var length = nodesCopy.length
		var randomIndex = getRandomInt(0, length)
		path.push(nodesCopy[randomIndex])

		nodesCopy.splice(randomIndex, 1)
	}

	return path
}

function retrieveNodes() {
	superagent.get(directoryIP + directoryPath + directoryListPath)
	.end((err, res) =>  {
		if(res.body.hasOwnProperty("nodes")) {
			nodes = res.body.nodes
		}
	})
}

function init(host, port) {
	retrieveNodes()
}

module.exports = {
	init: init,
	router: router
}