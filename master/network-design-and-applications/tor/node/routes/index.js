const fs = require("fs")
const NodeRSA = require("node-rsa")
const superagent = require("superagent")

var express = require("express")
var router = express.Router()

var privateSuffix = "private.pem"
var publicSuffix = "public.pem"

var privatePath
var publicPath

var privateKeyFormat = "pkcs8-private-pem"
var publicKeyFormat = "pkcs8-public-pem"

var privateKey
var publicKey

var directoryIP = "localhost:3000"
var directoryPath = "/nodes"
var directoryAddPath = "/add"
var directoryRemovePath = "/remove"

var localIP
var localPort

var eventFunctions = {}

router.use(function timeLog(req, res, next) {
	//console.log("Time: ", Date.now())
	next()
})

router.get("/", function(req, res) {
	var payload = req.query.payload
	var uncrypted = privateKey.decrypt(payload, "utf8")
	var eventObject = JSON.parse(uncrypted)

	if(eventObject.hasOwnProperty("event")) {
		eventFunctions[eventObject.event](req, res, eventObject.payload)
	}
})

function eventRelay(req, res, payload) {
	console.log("-----------------------------------------")
	console.log("Relaying Request to: %s", payload.destination)
	console.log("-----------------------------------------")
	var request = superagent.get(payload.destination)
	request = request.query({
		payload: payload.payload
	})
	request.end((err, forwardedRes) => {	
		res.json({payload: privateKey.encryptPrivate(forwardedRes.body.payload, "base64")})
	})
}

function eventFetch(req, res, payload) {
	console.log("------------------------------------------")
	console.log("Fetching content at: %s", payload.destination)
	console.log("------------------------------------------")
	var request = superagent[payload.method](payload.destination)
	
	// Set headers
	if(payload.hasOwnProperty("headers")) {
		Object.keys(payload.headers).forEach(function(key) {
			var value = payload.headers[key]
			request.set(key, value)
		})
	}

	// Set query parameters
	if(payload.hasOwnProperty("queries")) {
		Object.keys(payload.queries).forEach(function(key) {
			var value = payload.queries[key]
			request.query(key, value)
		})
	}

	// If we have files attached we are doing need to attach them, attaching them means we can't use request.send for the body
	if (payload.hasOwnProperty("files") && payload.files && payload.files.length > 0) {
		for(var i = 0; i < payload.files.length; i++) {
			request.attach(payload.files[i].fieldname, new Buffer(payload.files[i].buffer), payload.files[i].originalname)
		}
		// So we also need to send the body fields if we have some, these should be in json in this case
		if (payload.hasOwnProperty("body") && payload.body && Object.keys(payload.body).length > 0) {
			var keys = Object.keys(payload.body)
			for(var i = 0; i < keys.length; i++) {
				request.field(keys[i], payload.body[keys[i]])
			}
		}
	}
	// If we do not have files we might still have a body, just send it
	else if (payload.hasOwnProperty("body") && payload.body && Object.keys(payload.body).length === 0 && payload.body.constructor === Object) {
		request.send(payload.body)
	}

	request.end((err, forwardedRes) => {
		if(err) {
			if(err.status) {
				sendReply(res, err.response)
			} else {
				console.error("Network error on ", payload.destination)
				sendReply(res, {
					statusCode: 500,
					body: "Unknown error ocurred!",
				})
			}
		}
		else {
			sendReply(res, forwardedRes)
		}
	})
}

// Send website response back as reply to previoius node
function sendReply(res, forwardedRes) {
	// Values we are going to copy from the response object, these will get forwarded to the client
	var copyAttributes = ["cookie", "location", "text", "body", 
	"files", "buffered", "headers", "statusCode", "statusType", 
	"info", "ok", "redirect", "clientError", "serverError", "error", 
	"accepted", "noContent", "badRequest", "unauthorized", "notAcceptable", 
	"forbidden", "notFound", "type", "links", "redirects"]
	
	var payload = {}

	// Copy values into payload
	for(var index = 0; index < copyAttributes.length; index++) {
		var attribute = copyAttributes[index]
		if(forwardedRes.hasOwnProperty(attribute))
			payload[attribute] = forwardedRes[attribute]
	}
	try {
		res.json({payload: privateKey.encryptPrivate(JSON.stringify(payload), "base64")})
	}
	catch(error) {
		console.log("Error")
		console.log(error)
	}
}

function announceToDirectory() {
	superagent.post(directoryIP + directoryPath + directoryAddPath)
	.send({
		host: localIP,
		port: localPort, 
		publicKey: publicKey.exportKey(publicKeyFormat)
	})
	.end((err, res) => {
		if(err) {
			console.log(err)
		}
		else {
			console.log("Added ourselves to directory server")
		}
	})
}

function removeFromDirectory(callback) {
	console.log("Removing ourselves from directory server...")
	superagent.delete(directoryIP + directoryPath + directoryRemovePath)
	.send({
		host: localIP,
		port: localPort
	})
	.end((err, res) => {
		if(err) {
			console.log(err)
			callback()
		}
		else {
			console.log("Removed ourselves from directory server")
			callback()
		}
	})
}

function loadKeys(privatePath, publicPath) {
	console.log("Loading RSA Keypair from file")
	var privateKeyString = fs.readFileSync(privatePath)
	var publicKeyString = fs.readFileSync(publicPath)

	privateKey = new NodeRSA()
	privateKey.importKey(privateKeyString, privateKeyFormat)

	publicKey = new NodeRSA()
	publicKey.importKey(publicKeyString, publicKeyFormat)
}

function saveKeys(privatePath, publicPath) {
	console.log("Saving RSA Keypair to file")
	fs.writeFileSync(privatePath, privateKey.exportKey(privateKeyFormat))
	fs.writeFileSync(publicPath, publicKey.exportKey(publicKeyFormat))
}

function generateKeys(privatePath, publicPath) {
	console.log("Generating RSA Keypair...")
	
	if(!fs.existsSync("./keys")) {
		console.log("Key directory doesn't exist, creating...")
		fs.mkdirSync("./keys")
	}

	if(!fs.existsSync("./keys/" + localPort)) {
		console.log("Key directory for %d doesn't exist, creating...", localPort)
		fs.mkdirSync("./keys/" + localPort)
	}
	
	key = new NodeRSA()
	key.generateKeyPair()
	
	privateKey = new NodeRSA()
	publicKey = new NodeRSA()

	privateKey.importKey(key.exportKey(privateKeyFormat), privateKeyFormat)
	publicKey.importKey(key.exportKey(publicKeyFormat), publicKeyFormat)

	saveKeys(privatePath, publicPath)
}

function init(host, port) {
	initEventCallbacks()

	localIP = host
	localPort = port

	privatePath = "./keys/" + port + "/" + privateSuffix
	publicPath = "./keys/" + port + "/" + publicSuffix 

	if(fs.existsSync(privatePath) && fs.existsSync(publicPath)) {
		loadKeys(privatePath, publicPath)
	}
	else {
		generateKeys(privatePath, publicPath)
	}

	announceToDirectory()
}

function destroy(callback) {
	removeFromDirectory(callback)
}

function initEventCallbacks() {
	eventFunctions["relay"] = eventRelay
	eventFunctions["fetch"] = eventFetch
}

module.exports = {
	init: init,
	destroy: destroy,
	router: router
}