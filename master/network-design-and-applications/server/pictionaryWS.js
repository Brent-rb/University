var WebSocket = require("ws")
var uuid = require("uuid")
const fs = require("fs")

var wsServer
var eventFunctions = {}
var rooms = {}
var users = {}
var words = []
var games = []

// Clock which drives automatic updates to the active game states.
const secondClock = setInterval(clockTick, 1000)

function init(server, sessionParser) {
	wsServer = new WebSocket.Server({
		verifyClient: (info, done) => {
			sessionParser(info.req, {}, () => {
				done(info.req.session)
			})
		},
		server
	})

	words = fs.readFileSync("words.txt").toString().split("\n")

	rooms = []
	initEventFunctions()

	//wsServer.on("request", onWebsocketRequest)
	wsServer.on("connection", onWebscoketConnection)
}

// Link message events to functions
function initEventFunctions() {
	eventFunctions["set-username"] = eventSetUsername
	eventFunctions["list-rooms"] = eventListRooms
	eventFunctions["create-room"] = eventCreateRoom
	eventFunctions["join-room"] = eventJoinRoom
	eventFunctions["leave-room"] = eventLeaveRoom
	eventFunctions["chat-to-room"] = eventChatToRoom
	eventFunctions["ice-candidate"] = eventICECandidate
	eventFunctions["sdp-offer"] = eventSDPOffer
	eventFunctions["mouse-move"] = eventMouseMove
	eventFunctions["update-draw"] = eventUpdateDraw
	eventFunctions["start-game"] = eventStartGame
	eventFunctions["stop-game"] = eventStopGame
}

// Send an "Event" object to connection with a payload
function sendEvent(userId, connection, event, data) {
	try {
		connection.send(JSON.stringify({
			type: "event",
			event: event,
			data: data
		}))
	}
	catch(e) {
		console.log("Detected closed socket, removing user: %s", users[userId].username)
		removeUser(userId)
	}
}

function removeUser(userId) {
	var user = users[userId]
	if(user.room != null && rooms.hasOwnProperty(user.room)) {
		removeUserFromRoom(userId, user.room)
	}
	delete users[user.id]
}

// Event: mouse-move
// Tunnels the received data directly to other people in the room, including the 
// sender himself
function eventMouseMove(connection, session, data) {
	// TODO; Test if the data contains the same ID as session user

	// If user is in a room, send to all participants
	if(users[session.id].room != null) {
		var room = rooms[users[session.id].room]
		
		for(var key in room.users) {
			sendEvent(users[key].id, users[key].connection, "mouse-move", data)
		}
	}
}

// Event: update-draw
// Tunnels the received data directly to other people in the room, including the 
// sender himself
function eventUpdateDraw(connection, session, data) {
	// TODO; Test if the data contains the same ID as session user

	// If user is in a room, send to all participants
	if(users[session.id].room != null) {
		var room = rooms[users[session.id].room]

		// When there is an active game, only the player 'it' is allowed to send updates.
		if(room.activeGame != null && room.activeGame.active == true) {
			if(room.activeGame.itId !== session.id) return
		}
		
		for(var key in room.users) {
			sendEvent(users[key], users[key].connection, "update-draw", data)
		}
	}
}

// Event: set-username
// Function updates session username and sends new username to other people in the room
function eventSetUsername(connection, session, data) {
	// Retrieve information
	session.username = data.username
	users[session.id].username = data.username

	// Let user know he got a new username
	sendEvent(session.id, connection, "new-username", {
		username: data.username,
		id: session.id
	})

	// If user is in a room, let everyone in the room know he has a new username
	if(users[session.id].room != null) {
		var room = rooms[users[session.id].room]
		
		for(var key in room.users) {
			sendEvent(users[key].id, users[key].connection, "changed-username", {
				id: session.id,
				username: data.username
			})
		}
	}
}

// Event: list-rooms
// Function retrieves the list of open rooms and sends them back in JSON format
function eventListRooms(connection, session, data) {
	var newRooms = []

	for(var key in rooms) {
		var room = rooms[key]
		newRooms.push(room)
	}
	sendEvent(session.id, connection, "list-rooms", {rooms: newRooms})
}


// Function that sends an event to the user that he needs to join the given room
function joinRoom(userId, roomId) {
	// Link user to this room
	users[userId].room = roomId

	sendEvent(userId, users[userId].connection, "join-room", {
		room: {
			name: rooms[roomId].name,
			id: rooms[roomId].id,
			players: rooms[roomId].players,
			users: rooms[roomId].users,
			activeGame: rooms[roomId].activeGame,
		}
	})
}

function eventLeaveRoom(connection, session, data) {
	console.log("User left the room")
	var user = users[session.id]
	var room = user.room

	if(room != null) {
		this.removeUserFromRoom(user.id, room.id)

		if(room.activeGame != null) {
			stopGame(room.activeGame)
		}
	}	
}

// Function for when a user NEWLY connects to a room
// Let user know he needs to join that room
// Let other people in the room know there is a new client
function connectToRoom(userId, roomId) {
	var room = rooms[roomId]
	var user = users[userId]

	// Add client to users in the room
	room.users[user.id] = {
		id: user.id,
		username: user.username
	}

	// Let client join this room
	joinRoom(userId, roomId)
	// Let other users know there is a new client
	for(var key in rooms[roomId].users) {
		if(key === userId) {
			continue
		}

		sendEvent(users[key].id, users[key].connection, "connect-to-room", {
			user: {
				id: userId,
				username: users[userId].username
			}
		})
	}
}

// Function for when a user RECONNECTS to a room
// Let user know he needs to join that room
// Let other people in the room know this client reconnected
function reconnectToRoom(userId, roomId) {
	rooms[roomId].users[userId].username = users[userId].username
	joinRoom(userId, roomId)

	for(var key in rooms[roomId].users) {
		if(key == userId)
			continue

		sendEvent(users[key].id, users[key].connection, "reconnect-to-room", {
			user: {
				id: userId,
				username: users[userId].username
			}
		})
	}
}

// Event: join-room
// Function checks if user was already in a room and if so reconnects
// Else connect to new room if not full
// Else let client know room is full
function eventJoinRoom(connection, session, data) {
	var room = rooms[data.room]
	
	if(session.id in room.users) {
		reconnectToRoom(session.id, data.room)
	}
	else if(Object.keys(room.users).length < room.players) {
		connectToRoom(session.id, data.room)
	}
	else {
		sendEvent(session.id, connection, "join-refused", {
			reason: "Room is full"
		})
	}
}

// Event: create-room
// Function creates a new room
function eventCreateRoom(connection, session, data) {
	var id = uuid.v4()
	rooms[id] = {
		id: id,
		name: data.name,
		players: data.players,
		users: {},
		activeGame: null,
	}
	connectToRoom(session.id, id)

	for(var key in users) {
		var user = users[key]
		console.log("Sending new room to %s", user.username)
		if(user.room == null) {
			sendEvent(user.id, user.connection, "new-room", {
				room: rooms[id]
			})
		}
	}
}

function sendMessageToRoom(userId, roomId, message) {
	var room = rooms[roomId]

	for(var key in room.users) {
		var user = users[room.users[key].id]
		sendEvent(user.id, user.connection, "chat-to-room", {
			author: {
				id: userId,
				username: users[userId].username,
			},
			message: message,
			timestamp: new Date().toUTCString()
		})
	}
}

function eventChatToRoom(connection, session, data) {
	var user = users[session.id]
	sendMessageToRoom(user.id, user.room, data.message)
}

function eventICECandidate(connection, session, data) {
	var sender = users[session.id]
	var receiver = users[data.user.id]

	if(sender.room === receiver.room) {
		sendEvent(receiver.id, receiver.connection, "ice-candidate", {
			user: {
				id: sender.id
			},
			ice: {
				candidate: data.ice.candidate
			}
		})
	}
}

function eventSDPOffer(connection, session, data) {
	var sender = users[session.id]
	var receiver = users[data.user.id]

	if(sender.room === receiver.room) {
		sendEvent(receiver.id, receiver.connection, "sdp-offer", {
			user: {
				id: sender.id
			},
			sdp: {
				offer: data.sdp.offer
			}
		})
	}
}

// Every tick the active games are polled and necessary updates are sent to participants
function clockTick() {
	// Filters games which are marked as active
	function onlyActiveGames(game) {
		return game.active
	}
	
	var currentTime = new Date().getTime()
	var activeGames = games.filter(onlyActiveGames)
	for(var i = 0; i < activeGames.length; ++i) {
		var game = activeGames[i]
		var timeDiffSeconds = Math.floor((game.timeout - currentTime) / 1000)
		var room = rooms[game.roomId]

		if (timeDiffSeconds < 0) {
			// Shutdown game ourselves!
			stopGame(game)
		}
		else if(timeDiffSeconds <= 10) {
			var roomUsers = room.users
			// Send to all participants that the game will end soon
			for(var key in roomUsers) {
				sendEvent(users[key].id, users[key].connection, "chat-to-room", {
					author: {
						id: 0,
						username: "Server",
					},
					message: "Seconds left: " + timeDiffSeconds.toString(),
					timestamp: new Date().toUTCString()
				})
			}
		}
	}
}

// Event: start-game
// Starts a game within the room of the requester
function eventStartGame(connection, session, data) {
	var user = users[session.id]
	if(user.room != null) { // Requester must be IN a room
		var room = rooms[users[session.id].room]

		if(room.activeGame != null) { // Room must NOT have an active game
			sendEvent(users[session.id].id, users[session.id].connection, "chat-to-room", {
				author: {
					id: 0,
					username: "Server",
				},
				message: "There is already a game running, make sure to stop that one before starting a new one.",
				timestamp: new Date().toUTCString()
			})
			return
		}

		var roomUsers = room.users
		if(roomUsers.length < 2) { // Must have at least 2 participants in the room
			for(var key in users) {
				sendEvent(users[key].id, users[key].connection, "chat-to-room", {
					author: {
						id: 0,
						username: "Server",
					},
					message: "Minimal of 2 users required to start a new game",
					timestamp: new Date().toUTCString()
				})
			}
			return
		}
		
		startGame(room)
	}
}

// Event: stop-game
// Stops the active game inside the room of the requester.
function eventStopGame(connection, session, data) {
	var user = users[session.id]
	if(user.room != null) { // Requester must be IN a room
		var room = rooms[user.room]

		if(room.activeGame == null) { // Room MUST have an active game
			sendEvent(user.id, user.connection, "chat-to-room", {
				author: {
					id: 0,
					username: "Server",
				},
				message: "There is no game running.",
				timestamp: new Date().toUTCString()
			})
			return
		}

		var activeGame = room.activeGame
		if(activeGame.itId != session.id) { // Only the player who is 'it' can end the game!
			sendEvent(user.id, user.connection, "chat-to-room", {
				author: {
					id: 0,
					username: "Server",
				},
				message: "You are not allowed to do that!",
				timestamp: new Date().toUTCString()
			})
			return
		}

		stopGame(activeGame)
	}
}

// Creates and links a new game object for the provided room
function startGame(room) {
	if(room == null || room.users.length < 2) return

	var roomUsers = room.users
	var usersKeys = Object.keys(users)

	// Pick user to be 'it' and a word at random
	var randIdx = Math.floor(Math.random() * usersKeys.length)
	var pickedUserId = usersKeys[randIdx]
	
	randIdx = Math.floor(Math.random()*words.length)
	var pickedWord = words[randIdx]

	var currentTime = new Date().getTime()
	var timeout = currentTime + 1*60*1000 // Advance 1 minute
	// var timeout = currentTime + 20*1000 // Advance 20 seconds

	// Build new game
	var game = {
		active: true,
		roomId: room.id,
		itId: pickedUserId,
		word: pickedWord,
		start: currentTime, // Start moment is milliseconds sinds epoch
		timeout: timeout, // End moment is milliseconds sinds epoch
	}
	// .. and store it inside the room object
	room.activeGame = game
	games.push(game)

	// Notify users of update game within room
	for(var key in room.users) {
		sendEvent(users[key].id, users[key].connection, "update-room", {
			name: room.name,
			id: room.id,
			// players: rooms[roomId].players,
			// users: rooms[roomId].users,
			activeGame: room.activeGame,
		})
	}

	// Send message to 'it' with the thing it needs to draw
	sendEvent(users[pickedUserId].id, users[pickedUserId].connection, "chat-to-room", {
		author: {
			id: 0,
			username: "Server",
		},
		message: "You are 'it', the word is: " + pickedWord + "\nPress end-game when other have guessed that word",
		timestamp: new Date().toUTCString()
	})
}

// Marks and unlinks the provided game object as finished.
function stopGame(game) {
	if(game == null || game.active == false) return

	var room = rooms[game.roomId]
	// Remove the active game and send updates to the room
	game.active = false // Games are not cleaned up, they are just marked inactive

	if(room != null) {
		room.activeGame = null
		for(var key in room.users) {
			sendEvent(users[key].id, users[key].connection, "update-room", room)
			sendEvent(users[key].id, users[key].connection, "chat-to-room", {
				author: {
					id: 0,
					username: "Server",
				},
				message: "Game ended.",
				timestamp: new Date().toUTCString()
			})
		}
	}	
}

function removeRoom(roomId) {
	console.log("Deleting room: " + roomId)
	// Remove the active game (if any) before removing the room
	stopGame(rooms[roomId].activeGame)
	delete rooms[roomId]

	for(var key in users) {
		var user = users[key]

		if(user.room == null) {
			sendEvent(user.id, user.connection, "deleted-room", {
				room: {
					id: roomId
				}
			})
		}
	}
}

function removeUserFromRoom(userId, roomId) {
	var room = rooms[roomId]
	delete room.users[userId]

	if(Object.keys(room.users).length == 0) {
		removeRoom(roomId)
	}
	else {
		for(var key in room.users) {
			var user = users[key]
			sendEvent(user.id, user.connection, "disconnect-from-room", {
				user: {
					id: userId,
					username: users[userId].username
				}
			})
		}
	}
}

function onWebscoketConnection(connection, request) {
	var session = request.session
	checkNewUser(connection, session)
	
	connection.on("message", function(message) {
		onWebsocketMessage(connection, session, message)
	})
	connection.on("close", function(reasonCode, description) {
		onWebsocketClose(connection, session, reasonCode, description)
	})
}

function checkNewUser(connection, session) {
	if(users[session.id] === undefined) {
		createNewUser(connection, session)
	}
	else if(users[session.id].room != null) {
		if(rooms[users[session.id].room] !== undefined) {
			eventJoinRoom(connection, session, {
				room: users[session.id].room.id
			})
		}
		else {
			users[session.id].room = null
		}
	}
}

function createNewUser(connection, session) {
	users[session.id] = {
		id: session.id,
		username: "New User",
		connection: connection,
		room: null
	}

	eventSetUsername(connection, session, {
		username: "New User"
	})
}

function onWebsocketMessage(connection, session, message) {
	console.log("Received Message: " + message)
		
	var object = JSON.parse(message)
	if(object.type == "event") {
		eventFunctions[object.event](connection, session, object.data)
	}

	session.save()
}

function onWebsocketClose(connection, session, reasonCode, description) {
	if(session.id !== undefined) {
		removeUser(session.id)
	}
}

module.exports = {
	init: init
}