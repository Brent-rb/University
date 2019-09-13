import React, { Component } from 'react';
import Subheader from 'material-ui/Subheader';
import Paper from 'material-ui/Paper';
import RaisedButton from 'material-ui/RaisedButton';
import TextField from 'material-ui/TextField';
import EditorTitle from 'material-ui/svg-icons/editor/title'
import SocialPerson from 'material-ui/svg-icons/social/person'
import Slider from 'material-ui/Slider'

import './RoomCreator.css';

class RoomCreator extends Component {
	state = {
		name: "",
		roomSize: 2,
		error: ""
	}

	constructor(props) {
		super(props) 

		this.changeNameValue = this.changeNameValue.bind(this)
		this.changeSliderValue = this.changeSliderValue.bind(this)
		this.createRoom = this.createRoom.bind(this)
	}

	render() {
		return (
			<div className="RoomCreator-container">
				<Paper className="RoomCreator-paper" zDepth={1}>
					<Subheader>Room Settings</Subheader>
					<div className="RoomCreator-form-container">
						<div className="RoomCreator-textfield-container">
							<EditorTitle />
							<TextField 
								hintText="Room Name"
								value={this.state.name}
								onChange={this.changeNameValue} 
							/>
						</div>
						<div className="RoomCreator-textfield-container">
							<SocialPerson />
							<p>{"Room Size: " + this.state.roomSize}</p>
							<Slider
								min={2}
								max={8}
								step={1}
								value={this.state.roomSize}
								onChange={this.changeSliderValue}
								sliderStyle={{marginTop: "0px", marginBottom: "0px"}}
							/>
						</div>
					</div>
					<div className="RoomCreator-button-container">
						<RaisedButton className="RoomCreator-button" label="Create" onClick={this.createRoom} primary={true} />
						<span>{this.state.error}</span>
					</div>
				</Paper>
			</div>
		);
	}

	createRoom() {
		if(!this.props.websocket.isConnected()) {
			console.log("Not connected")
			this.setState({error: "Error: Not connected to server."})
		}
		else {
			this.props.websocket.createRoom(this.state.name, this.state.roomSize)
			this.props.onDone()
		}
	}

	changeNameValue(event, value) {
		this.setState({name: value})
	}

	changeSliderValue(event, value) {
		this.setState({roomSize: value})
	}
}

export default RoomCreator;
