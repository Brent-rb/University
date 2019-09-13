// Module imports
const express = require("express") // Module for routing
const http = require("http")
const fs = require("fs")

const app = express()
const fallback_port = 4001

const args = process.argv.slice(2)
const argc = args.length
var indexRoute = require("./routes/index")

function exitHandler(options, err) {
	console.error(err)
	
	indexRoute.destroy(() => {
		process.exit()
	})
}

//do something when app is closing
process.on('exit', exitHandler.bind(null,{cleanup:true}));

//catches ctrl+c event
process.on('SIGINT', exitHandler.bind(null, {exit:true}));

// catches "kill pid" (for example: nodemon restart)
process.on('SIGUSR1', exitHandler.bind(null, {exit:true}));
process.on('SIGUSR2', exitHandler.bind(null, {exit:true}));

//catches uncaught exceptions
process.on('uncaughtException', exitHandler.bind(null, {exit:true}));

if (argc > 0) {
	var port_number = parseInt(args[0])
}
else {
	var port_number = fallback_port
}

// Import routes
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