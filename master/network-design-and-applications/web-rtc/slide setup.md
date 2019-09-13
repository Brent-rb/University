# WebSocket/WebRTC
> Berghmans Brent & Proesmans Bert

# Componenten
* Front-end
    * Single page application
    * 
* Back-end
    * Aanleveren van statische content
    * Websocket endpoint
        * Signaling server

# Front-end
* React applicatie
    * Component based
    * Serverstate single point of truth
* Websocket communicatie
* WebRTC setup

```js
// /client/src/Pictionary.js:45-61
render() {
    return (
        <div className="Pictionary-container">
            <AppBar
                className="Pictionary-AppBar"
                title="Pictionary"
                showMenuIconButton={this.state.navStack.length > 1}
                iconElementLeft={<IconButton><NavigationArrowBack /></IconButton>}
                iconElementRight={<UsernameChanger user={this.state.user} websocket={this.websocket} />}
                onLeftIconButtonTouchTap={this.popNavStack}
            />
            {this.compareNavStack("RoomList") && <RoomList onCreateRoom={this.onCreateRoom} websocket={this.websocket} />}
            {this.compareNavStack("RoomCreator") && <RoomCreator onDone={this.popNavStack} websocket={this.websocket} />}
            {this.compareNavStack("Room") && <Room room={this.state.room} user={this.state.user} websocket={this.websocket} />}
        </div>
    );
}
```

```js
// /client/src/RoomCanvas.js:52-56
componentWillMount() {
    this.props.websocket.addCallback("mouse-move", this.mouseMove)
    this.props.websocket.addCallback("update-draw", this.updateDraw)
    this.props.websocket.addCallback("canvas-clear", this.clearCanvas)
}
```

# Back-end
* Node applicatie
* State transducer
    * Update verbonden clients

```js
// /server/pictionaryWS.js:34-48
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
```

# Prestaties

* Client stuurt maximaal 34 updates/s
* 95percentile updates <20 bytes
* Theoretisch max #clients: 25.000 (200Mbit)

Maar;
* Beperkt aantal descriptors
* Latency moet <20ms blijven

=~ 5.000 clients per server

# Demo
