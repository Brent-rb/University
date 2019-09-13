import React, { Component } from 'react';
import {List, ListItem} from 'material-ui/List';
import Subheader from 'material-ui/Subheader';
import Paper from 'material-ui/Paper';
import RaisedButton from 'material-ui/RaisedButton';

import './RoomList.css';

class RoomList extends Component {
	state = {
		rooms: []
	}

	constructor(props) {
		super(props)
		
		this.joinRoom = this.joinRoom.bind(this)
		this.listRooms = this.listRooms.bind(this)
		this.newRoom = this.newRoom.bind(this)
		this.deletedRoom = this.deletedRoom.bind(this)
	}

	componentWillMount() {
		this.props.websocket.addCallback("new-room", this.newRoom)
		this.props.websocket.addCallback("deleted-room", this.deletedRoom)
	}

	componentDidMount() {
		this.props.websocket.addCallback("list-rooms", this.listRooms)
		if(this.props.websocket.isConnected())
			this.props.websocket.getRooms()
		else
			this.props.websocket.addCallback("websocket-opened", () => {
				this.props.websocket.getRooms()
			})
	}

	componentWillUnmount() {
		this.props.websocket.removeCallback("list-rooms", this.listRooms)
		this.props.websocket.removeCallback("new-room", this.newRoom)
		this.props.websocket.removeCallback("deleted-room", this.deletedRoom)
	}

	render() {
		var roomsHTML = Object.keys(this.state.rooms).map((roomKey) => {
			var room = this.state.rooms[roomKey]
            return <ListItem onClick={this.joinRoom.bind(this, room.id)} primaryText={room.name} key={room.id} />;
        });

		return (
			<div className="RoomList-container">
				<Paper className="RoomList-paper" zDepth={1}>
					<List>
						<Subheader>Pictionary Rooms</Subheader>
						{roomsHTML}
					</List>
					<div className="RoomList-button-container">
						<RaisedButton className="RoomList-button" label="Create Room" onClick={this.props.onCreateRoom} primary={true} />
						<RaisedButton className="RoomList-button" label="Get Rooms" onClick={(e) => this.props.websocket.getRooms()} primary={true} />
					</div>
				</Paper>
			</div>
		);
	}

	addRoom(room) {
		var rooms = this.state.rooms
		rooms[room.id] = room
		this.setState({rooms: rooms})
	}

	removeRoom(roomId) {
		var rooms = this.state.rooms
		delete rooms[roomId]
		this.setState({rooms: rooms})
	}

	newRoom(data) {
		console.log("Add room")
		this.addRoom(data.room)
	}

	deletedRoom(data) {
		console.log("Delete room")
		this.removeRoom(data.room.id)
	}

	joinRoom(roomId) {
		this.props.websocket.joinRoom(roomId)
	}

	listRooms(data) {
		var rooms = {}
		for(var key in data.rooms) {
			rooms[data.rooms[key].id] = data.rooms[key]
		}
		console.log(rooms)
		this.setState({rooms: rooms})
	}
}

export default RoomList;
