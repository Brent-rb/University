const fs = require("fs")
var express = require("express")
var router = express.Router()
var nodes = require("../tor-nodes.json").nodes

console.log("Available tor-nodes:")
for(var index = 0; index < nodes.length; index++) {
	var node = nodes[index]
	console.log("\t%s:%d", node.host, node.port)
}

router.use(function timeLog(req, res, next) {
	//console.log("Time: ", Date.now())
	next()
})

router.get("/list", function(req, res) {
	console.log("Nodes requested.")
	res.json({ nodes: nodes })
})

router.post("/add", function(req, res) {
	var host = req.body.host
	var port = req.body.port
	var publicKey = req.body.publicKey
	var remoteIP = req.connection.remoteAddress

	// Localhost shows up as this
	if(remoteIP == "::ffff:127.0.0.1") {
		remoteIP = "localhost"
	}

	console.log("Node wants to register: %s:%d, Remote: %s", host, port, remoteIP)
	if(host && port && publicKey && host == remoteIP) {
		console.log("\tNode accepted")
		res.json({
			succes: true
		})

		addNode(host, port, publicKey)
	}
	else {
		console.log("\tNode rejected")
		res.json({
			succes: false
		})
	}
})

router.delete("/remove", function(req, res) {
	var host = req.body.host
	var port = req.body.port
	var remoteIP = req.connection.remoteAddress
	
	// Localhost shows up as this
	if(remoteIP == "::ffff:127.0.0.1") {
		remoteIP = "localhost"
	}
	
	console.log("Node wants to be removed: %s:%d, Remote: %s", host, port, remoteIP)
	if(host && port && host == remoteIP) {
		console.log("\tNode removed")
		res.json({
			succes: true
		})

		removeNode(host, port)
	}
	else {
		console.log("\tNode removal rejected")
		res.json({
			succes: false
		})
	}
})

function saveNodes() {
	fs.writeFile("tor-nodes.json", JSON.stringify({
		nodes: nodes
	}, null, 4), function(err) {
		if(err)
			console.log(err)
		else
			console.log("\tNode list saved to file.")
	})
}

function addNode(host, port, publicKey) {
	var newEntry = true

	for(var index = 0; index < nodes.length; index++) {
		var node = nodes[index]

		if(node.port == port && node.host == host) {
			console.log("\tHost already registered, updating public key.")
			node.publicKey = publicKey
			newEntry = false
			break;
		}
	}

	if(newEntry) {
		console.log("\tHost is new, adding to list")
		nodes.push({
			host: host,
			port: port,
			publicKey: publicKey
		})
	}

	saveNodes()
}

function removeNode(host, port) {
	for(var index = 0; index < nodes.length; index++) {
		var node = nodes[index]
		if(node.host == host && node.port == port) {
			nodes.splice(index, 1)
			break;
		}
	}

	saveNodes()
}

module.exports = router