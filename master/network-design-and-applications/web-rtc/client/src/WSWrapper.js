
class WSWrapper {
	constructor(host, port) {
		this.host = host
		this.port = port

		this.open = this.open.bind(this)
		this.onWebsocketOpen = this.onWebsocketOpen.bind(this)
		this.onWebsocketClose = this.onWebsocketClose.bind(this)
		this.onWebsocketMessage = this.onWebsocketMessage.bind(this)
		this.onWindowBeforeUnload = this.onWindowBeforeUnload.bind(this)

		this.callbacks = {}
		this.connected = false

		this.open()
	}

	open() {
		var ws_url = "wss://" + this.host
		if(this.port && this.port.length) {
			ws_url += ":" + this.port
		}

		this.websocket = new WebSocket(ws_url)
		this.websocket.onopen = this.onWebsocketOpen
		this.websocket.onclose = this.onWebsocketClose
		this.websocket.onmessage = this.onWebsocketMessage
		window.onbeforeunload = this.onWindowBeforeUnload
	}

	onWebsocketOpen() {
		console.log("Websocket Open")
		this.connected = true
		this.callCallbacks("websocket-opened", {})
	}

	onWebsocketClose() {
		console.log("Websocket Closed")
		this.connected = false
		this.callCallbacks("websocket-closed", {})
	}

	onWebsocketMessage(event) {
		var message = event.data
		var object = JSON.parse(message)
		
		if(object.type === "event") {
			this.callCallbacks(object.event, object.data)
		}
	}

	onWindowBeforeUnload(event) {
		this.websocket.close()
	}

	callCallbacks(eventName, data) {
		if(eventName in this.callbacks) {
			for(var i = 0; i < this.callbacks[eventName].length; i++) {
				this.callbacks[eventName][i](data)
			}
		}
	}

	addCallback(eventType, callback) {
		if(eventType in this.callbacks) {
			if(this.callbacks[eventType].indexOf(callback) < 0) {
				this.callbacks[eventType].push(callback)
			} 
		}
		else {
			this.callbacks[eventType] = [callback]
		}
	}

	removeCallback(eventType, callback) {
		if(eventType in this.callbacks) {
			var indexOf = this.callbacks[eventType].indexOf(callback)
			if(indexOf >= 0) {
				this.callbacks[eventType].splice(indexOf, 1)
			}
		}
	}

	createEvent(eventName, payload) {
		var object = {
			type: "event",
			event: eventName,
			data: payload 
		}

		return object
	}

	sendEvent(eventName, payload) {
		var object = this.createEvent(eventName, payload)
		if(this.connected) {
			this.websocket.send(JSON.stringify(object))
		}
	}

	getRooms() {
		this.sendEvent("list-rooms", {})
	}

	createRoom(name, players) {
		this.sendEvent("create-room", {
			name: name,
			players: players
		})
	}

	joinRoom(roomId) {
		this.sendEvent("join-room", {
			room: roomId
		})
	}

	leaveRoom() {
		this.sendEvent("leave-room", {})
	}

	isConnected() {
		return this.connected
	}

	sendMessage(message) {
		this.sendEvent("chat-to-room", {
			message: message
		})
	}

	sendICECandidate(userId, candidate) {
		this.sendEvent("ice-candidate", {
			user: {
				id: userId
			},
			ice: {
				candidate: candidate
			}
		})
	}

	sendSDPOffer(userId, SDPOffer) {
		this.sendEvent("sdp-offer", {
			user: {
				id: userId
			},
			sdp: {
				offer: SDPOffer
			}
		})
	}

	sendMouseMove(userId, cords) {
		this.sendEvent("mouse-move", {
			user: {
				id: userId,
			},
			cordinates: cords
		})
	}

	sendDrawUpdate(userId, beginCordinates, endCordinates) {
		this.sendEvent("update-draw", {
			user: {
				id: userId,
			},
			beginCordinates: beginCordinates,
			endCordinates: endCordinates,
		})
	}

	setUsername(username) {
		this.sendEvent("set-username", {
			username: username
		})
	}

	sendStartGame() {
		this.sendEvent("start-game", {})
	}

	sendStopGame() {
		this.sendEvent("stop-game", {})
	}
}

export default WSWrapper;