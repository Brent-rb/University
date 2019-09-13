// Module imports
const express = require("express") // Module for routing
const http = require("http")
const fs = require("fs")
const bodyParser = require("body-parser")

const app = express()
const fallback_port = 3000

const args = process.argv.slice(2)
const argc = args.length

if (argc > 0) {
	var port_number = parseInt(args[0])
}
else {
	var port_number = fallback_port
}

// Import routes
var nodesRoute = require("./routes/nodes")

// Middlewares
// Middleware for POST parameters
app.use(bodyParser.json())
app.use(bodyParser.urlencoded({ extended: true }))

// Activate routes
app.use("/nodes", nodesRoute)

// Start server
var httpServer = http.createServer(app)
httpServer.listen(port_number, function () {
	var host = httpServer.address().address
	var port = httpServer.address().port
	console.log("Server running at http://%s:%s", host, port)
})