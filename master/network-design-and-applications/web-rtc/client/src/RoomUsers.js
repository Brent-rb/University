import React, { Component } from 'react';
import Subheader from 'material-ui/Subheader';
import Paper from 'material-ui/Paper';

import './RoomUsers.css';

class RoomUsers extends Component {
	state = {
		users: {

		}
	}

	constructor(props) {
		super(props)

		this.userMedia = null
		this.iceServers = {
			iceServers: [
				// {
				// 	url: "stun:stunserver.com:12345"
				// }
				// Some public stun servers
				{
					url: "stun:stun.sipgate.net"
				},
				{
					url: "stun:stun.sipgate.net:10000"
				},
				// Turn server (includes STUN funcionality)
				// {
				// 	url: "",
				// }
			]
		}

		this.changedUsername = this.changedUsername.bind(this)
		this.userConnectedToRoom = this.userConnectedToRoom.bind(this)
		this.userReconnectedToRoom = this.userReconnectedToRoom.bind(this)
		this.userDisconnectedFromRoom = this.userDisconnectedFromRoom.bind(this)
		this.sdpOffer = this.sdpOffer.bind(this)
		this.iceCandicate = this.iceCandicate.bind(this)
	}

	componentWillMount() {
		this.setState({users: this.props.users})

		this.props.websocket.addCallback("changed-username", this.changedUsername)
		this.props.websocket.addCallback("connect-to-room", this.userConnectedToRoom)
		this.props.websocket.addCallback("reconnect-to-room", this.userReconnectedToRoom)
		this.props.websocket.addCallback("disconnect-from-room", this.userDisconnectedFromRoom)
		this.props.websocket.addCallback("sdp-offer", this.sdpOffer)
		this.props.websocket.addCallback("ice-candidate", this.iceCandicate)
	}

	componentDidMount() {
		var constraints = {
			audio: false, // Switch this to true for audio
			video: {
				facingMode: "user",
				width: 720,
				height: 480
			}
		}

		navigator.mediaDevices.getUserMedia(constraints).then((stream) => {
			var users = Object.assign({}, this.state.users)
			users[this.props.user.id].stream = stream

			if(this.hasOwnProperty("mediaDevicesQueue")) {
				//console.log("There are " + this.mediaDevicesQueue.length + " connections waiting")
				for(var i = 0; i < this.mediaDevicesQueue.length; i++) {
					var user = users[this.mediaDevicesQueue[i]]
					user.peerConnection.addStream(stream)
					user.peerConnection.createAnswer((answer) => {
						console.log("Created answer")
						user.peerConnection.setLocalDescription(answer)
						this.props.websocket.sendSDPOffer(user.id, answer)
					}, (error) => {
						console.log(error)
					})
				}
				this.mediaDevicesQueue = []
			}

			this.userMedia = stream
			this.setState({ users: users })
		})
		.catch((err) => {

		})
	}

	componentWillUnmount() {
		this.props.websocket.removeCallback("changed-username", this.changedUsername)
		this.props.websocket.removeCallback("connect-to-room", this.userConnectedToRoom)
		this.props.websocket.removeCallback("reconnect-to-room", this.userReconnectedToRoom)
		this.props.websocket.removeCallback("disconnect-from-room", this.userDisconnectedFromRoom)
		this.props.websocket.removeCallback("sdp-offer", this.sdpOffer)
		this.props.websocket.removeCallback("ice-candidate", this.iceCandicate)
	}

	render() {
		var usersHTML = Object.keys(this.state.users).map((userKey) => {
			var user = this.state.users[userKey]
			return (
				<Paper key={user.id} className="Room-user-container">
					{user.hasOwnProperty("stream") && <video key={user.stream.id} src={URL.createObjectURL(user.stream)} autoPlay />}
					<Subheader>{user.username}</Subheader>
				</Paper>
			)
		})

		return (
			<div className="Room-pictionary-users-container">
				{usersHTML}
			</div>
		)
	}

	changedUsername(data) {
		var newUsers = Object.assign({}, this.state.users)

		newUsers[data.id].username = data.username
		this.setState({ users: newUsers })
	}

	userConnectedToRoom(data) {
		var newUsers = Object.assign({}, this.state.users)
		var user = data.user

		user.peerConnection = new RTCPeerConnection(this.iceServers)
		user.peerConnection.onicecandidate = (event) => {
			if (event.candidate) {
				console.log(event.candidate)
				this.props.websocket.sendICECandidate(user.id, event.candidate)
			}
		}

		/*
		user.peerConnection.ontrack = (event) => {
			console.log("Ontrack1")
			this.addTrack(user.id, event.streams)
		}
		*/
		user.peerConnection.onaddstream = (event) => {
			this.setStream(user.id, event.stream)
		}

		user.peerConnection.addStream(this.userMedia)
		//this.userMedia.getTracks().forEach(track => user.peerConnection.addTrack(track, this.userMedia))

		user.peerConnection.createOffer((offer) => {
			user.peerConnection.setLocalDescription(offer)
			this.props.websocket.sendSDPOffer(user.id, offer)
		}, (error) => {
			console.log(error)
		})

		newUsers[data.user.id] = data.user
		this.setState({ users: newUsers })
	}

	sdpOffer(data) {
		var newUsers = Object.assign({}, this.state.users)
		var newSender = Object.assign({}, newUsers[data.user.id])

		if (!(newSender.peerConnection)) {
			newSender.peerConnection = new RTCPeerConnection(this.iceServers)
			newSender.peerConnection.onicecandidate = (event) => {
				if (event.candidate) {
					this.props.websocket.sendICECandidate(newSender.id, event.candidate)
				}
			}

			/*
			sender.peerConnection.ontrack = (event) => {
				this.addTrack(sender.id, event.streams)
			}
			*/
			newSender.peerConnection.onaddstream = (event) => {
				this.setStream(newSender.id, event.stream)
			}

			if (this.userMedia != null) {
				//this.userMedia.getTracks().forEach(track => sender.peerConnection.addTrack(track, this.userMedia))			
				newSender.peerConnection.addStream(this.userMedia)
				newSender.peerConnection.createAnswer((answer) => {
					newSender.peerConnection.setLocalDescription(answer)
					this.props.websocket.sendSDPOffer(newSender.id, answer.sdp)
				}, (error) => {

				})
			}
			else {
				if(!this.mediaDevicesQueue) {
					this.mediaDevicesQueue = []
				}
				this.mediaDevicesQueue.push(newSender.id)
			}	
		}

		newSender.peerConnection.setRemoteDescription(new RTCSessionDescription(data.sdp.offer)).then((event) => {
			console.log("Remote Description added.")
		})
		newUsers[newSender.id] = newSender
		this.setState({users: newUsers})
	}

	iceCandicate(data) {
		if (data.ice.candidate) {
			if(this.state.users.hasOwnProperty(data.user.id) && this.state.users[data.user.id].hasOwnProperty("peerConnection")) {
				if(data.ice.candidate.hasOwnProperty("sdpMid") && data.ice.candidate.hasOwnProperty("sdpMLineIndex")) {
					this.state.users[data.user.id].peerConnection.addIceCandidate(new RTCIceCandidate(data.ice.candidate)).then((event) => {
						console.log("ICE Added")
					})
				}
			}
		}
	}

	setStream(userId, stream) {
		var newUsers = Object.assign({}, this.state.users)
		var newUser = Object.assign({}, newUsers[userId])
		newUser.stream = stream
		newUsers[newUser.id] = newUser

		this.setState({ users: newUsers })
	}

	addTrack(userId, tracks) {
		var newUsers = Object.assign({}, this.state.users)
		var newUser = Object.assign({}, newUsers[userId])

		if (!newUser.hasOwnProperty("stream")) {
			newUser.stream = new MediaStream()
		}
		for (var stream in tracks) {
			newUser.stream.addTrack(stream)
		}

		newUsers[newUser.id] = newUser
		this.setState({ users: newUsers })
	}

	userReconnectedToRoom(data) {
		//
	}

	userDisconnectedFromRoom(data) {
		var newUsers = Object.assign({}, this.state.users)
		delete newUsers[data.user.id]
		this.setState({ users: newUsers })
	}
}

export default RoomUsers;
