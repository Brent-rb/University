// Module imports
const express = require("express") // Module for routing
const app = express()
const http = require("http")
const https = require("https")
const fs = require("fs")
const session = require("express-session")
const pictionaryWS = require("./pictionaryWS")
const FALLBACK_PORT_NUMBER = 443

const args = process.argv.slice(2)
const argc = args.length

var port_number = FALLBACK_PORT_NUMBER
if (argc > 0) {
	var port_number = parseInt(args[0])
}

// Import routes
//var indexRoute = require("./routes/index")
//var websocketRoute = require("./routes/websocket")

var sessionParser = session({
	saveUninitialized: true,
	resave: true,
	secret: "twiceonce",
	cookie: {
		maxAge: 1000 * 60 * 60 * 24,
		sameSite: false
	}
})

// Activate routes
app.use(express.static("public"))
app.use(sessionParser)
//app.use("/", indexRoute)
//app.use("/websocket", websocketRoute)

// Start server
// Only setup an SSL connection when the default port is used.
if (port_number == FALLBACK_PORT_NUMBER) {
	const secure_options = {
		key: fs.readFileSync('client-key.pem'),
		cert: fs.readFileSync('client-cert.pem'),
	}
	var httpServer = https.createServer(secure_options, app)
} 
else {
	var httpServer = http.createServer(app)
}
pictionaryWS.init(httpServer, sessionParser)

httpServer.listen(port_number, function () {
	var host = httpServer.address().address
	var port = httpServer.address().port
	console.log("Server running at http://%s:%s", host, port)
})