// Module imports
const express = require("express") // Module for routing
var bodyParser = require('body-parser')
const http = require("http")
const fs = require("fs")

const app = express()
const fallback_port = 5000

const args = process.argv.slice(2)
const argc = args.length

if (argc > 0) {
	var port_number = parseInt(args[0])
}
else {
	var port_number = fallback_port
}

// parse application/x-www-form-urlencoded
app.use(bodyParser.urlencoded({ extended: false }))
// parse application/json
app.use(bodyParser.json())

// Import routes
var indexRoute = require("./routes/index")
indexRoute.init("localhost", port_number)
// Activate routes
app.use("/", indexRoute.router)

// Start server
var httpServer = http.createServer(app)
httpServer.listen(port_number, function () {
	var host = httpServer.address().address
	var port = httpServer.address().port
	console.log("Server running at http://%s:%s", host, port)
})