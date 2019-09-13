import React, { Component } from 'react';
import RoomCanvas from './RoomCanvas';
import RoomUsers from './RoomUsers';
import RoomChat from './RoomChat';

import './Room.css';

class Room extends Component {

	constructor(props) {
		super(props)

		this.updateRoom = this.updateRoom.bind(this)
	}

	componentWillMount() {
		this.props.websocket.addCallback("update-room", this.updateRoom)
	}

	componentDidMount() {}

	componentWillUnMount() {
		this.props.websocket.removeCallback("update-room", this.updateRoom)
		this.props.websocket.leaveRoom()
	}

	render() {
		return (
			<div className="Room-container">
				<RoomCanvas ref="roomCanvas" user={this.props.user} websocket={this.props.websocket} />
					
				<div className="Room-pictionary-container">
					<RoomUsers user={this.props.user} users={this.props.room.users} websocket={this.props.websocket} />
					<RoomChat user={this.props.user} websocket={this.props.websocket} />
				</div>
			</div>
		);
	}

	updateRoom(data) {
		console.log("updateRoom called", data)
		if(data != null) {
			this.refs.roomCanvas.onGameUpdate(data.activeGame)
		}
	}
}

export default Room;
