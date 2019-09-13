import React, { Component } from 'react';
import AppBar from 'material-ui/AppBar';
import IconButton from 'material-ui/IconButton';
import NavigationArrowBack from 'material-ui/svg-icons/navigation/arrow-back'
import FlatButton from 'material-ui/FlatButton'

import RoomList from './RoomList'
import RoomCreator from './RoomCreator'
import Room from './Room'
import UsernameChanger from './UsernameChanger'

import WSWrapper from './WSWrapper.js'

import './Pictionary.css';

class Pictionary extends Component {
	state = {
		navStack: ["RoomList"],
		user: {
			id: -1,
			username: ""
		},
		room: {},
	}

	constructor(props) {
		super(props)

		this.onCreateRoom = this.onCreateRoom.bind(this)
		this.pushNavStack = this.pushNavStack.bind(this)
		this.popNavStack = this.popNavStack.bind(this)
		this.onJoinRoom = this.onJoinRoom.bind(this)
		this.onNewUsername = this.onNewUsername.bind(this)
	}

	componentWillMount() {
		this.websocket = new WSWrapper(window.location.hostname, window.location.port)
	}

	componentDidMount() {
		this.websocket.addCallback("join-room", this.onJoinRoom)
		this.websocket.addCallback("new-username", this.onNewUsername)
	}

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

	compareNavStack(compareTo) {
		return this.peekNavStack() === compareTo
	}

	peekNavStack() {
		return this.state.navStack[this.state.navStack.length - 1];
	}

	pushNavStack(nav) {
		var navStack = this.state.navStack
		navStack.push(nav)
		this.setState({navStack: navStack})
	}

	popNavStack() {
		var navStack = this.state.navStack
		navStack.splice(-1, 1)
		this.setState({navStack: navStack})
	}

	onCreateRoom() {
		this.pushNavStack("RoomCreator")
	}

	onJoinRoom(data) {
		this.setState({room: data.room})
		this.pushNavStack("Room")
	}

	onNewUsername(data) {
		console.log("New username")
		this.setState({user: {
			username: data.username,
			id: data.id
		}})
	}
}

export default Pictionary;
