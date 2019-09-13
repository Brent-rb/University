import React, { Component } from 'react';
import { List, ListItem } from 'material-ui/List';
import Paper from 'material-ui/Paper';
import TextField from 'material-ui/TextField';
import RaisedButton from 'material-ui/RaisedButton';
import Subheader from 'material-ui/Subheader';

import './RoomChat.css'

class RoomChat extends Component {
	state = {
		chat: {
			log: [],
			input: ""
		}
	}

	// Last message of chat window
	messagesEnd = null

	constructor(props) {
		super(props)

		this.newMessage = this.newMessage.bind(this)

		this.changeChatInput = this.changeChatInput.bind(this)
		this.sendMessage = this.sendMessage.bind(this)

		this.scrollToBottom = this.scrollToBottom.bind(this)
	}

	componentWillMount() {
		this.props.websocket.addCallback("chat-to-room", this.newMessage)
	}

	componentDidMount() {

	}

	componentWillUnmount() {
		this.props.websocket.removeCallback("chat-to-room", this.newMessage)
	}

	componentDidUpdate() {
		this.scrollToBottom()
	}

	render() {
		var chatHTML = this.state.chat.log.map((chatline) => {
			return (
				<div className="Room-chat-item" key={"" + chatline.author.id + chatline.timestamp}>
					<div className="Room-chat-username">
						{chatline.author.username}
					</div>
					<div className="Room-chat-message">
						{chatline.message.split("\n").map(function(line, idx) {
							return (
								<span key={"" + chatline.author.id + chatline.timestamp + idx}>
									{line}<br/>
								</span>
							)
						})}
					</div>
				</div>
			)
		})

		return (
			<Paper className="Room-chat-container">
				<Subheader>Chatroom</Subheader>
				<div className="Room-chat-list">
					{chatHTML}
					<div style={{float:"left", clear:"both"}} ref={(el) => { this.messagesEnd = el;}}>
					</div>
				</div>
				<div className="Room-chat-input-container">
					<form onSubmit={this.sendMessage} >
						<TextField
							className="Room-chat-input"
							hintText="Send a message."
							value={this.state.chat.input}
							onChange={this.changeChatInput}
						/>
						<RaisedButton className="Room-chat-button" label="Send" onClick={this.sendMessage} primary={true} />
					</form>
				</div>
			</Paper>
		)
	}

	changeChatInput(event, value) {
		var newChat = Object.assign({}, this.state.chat)
		newChat.input = value;
		this.setState({
			chat: newChat
		})
	}

	sendMessage(event) {
		event.preventDefault()
		this.props.websocket.sendMessage(this.state.chat.input)

		var newChat = Object.assign({}, this.state.chat)
		newChat.input = ""
		this.setState({
			chat: newChat
		})
	}

	newMessage(data) {
		var newChat = Object.assign({}, this.state.chat)
		newChat.log.push(data)
		
		this.setState({
			chat: newChat
		})
	}

	scrollToBottom() {
		this.messagesEnd.scrollIntoView({behavior: "smooth"})
	}
}

export default RoomChat;