import React, { Component } from "react"
import FlatButton from 'material-ui/FlatButton'
import TextField from 'material-ui/TextField'

import './UsernameChanger.css'

class UsernameChanger extends Component {
	state = {
		mode: "display",
		editor: {
			input: ""
		}
	}
	
	constructor(props) {
		super(props)

		this.inDisplayMode = this.inDisplayMode.bind(this)
		this.inEditMode = this.inEditMode.bind(this)
		this.openEditor = this.openEditor.bind(this)
		this.closeEditor = this.closeEditor.bind(this)
		this.changeEditorInput = this.changeEditorInput.bind(this)
		this.onSubmit = this.onSubmit.bind(this)
	}

	componentWillMount() {
		this.setState({ editor: {
			input: this.props.user.username
		}})
	}

	componentDidMount() {

	}

	componentWillUnmount() {

	}

	render() {
		return (
			<div className="UsernameChanger-root">
				{ this.inDisplayMode() && <FlatButton label={this.props.user.username} onClick={this.openEditor} /> }
				{ this.inEditMode() && 
					<form onSubmit={this.onSubmit} className="UsernameChanger-form">
						<TextField className="UsernameChanger-input" ref="username-input" hintText="Username" value={this.state.editor.input} onChange={this.changeEditorInput} autoFocus/>
					</form>
				}
			</div>
		)
	}

	inDisplayMode() {
		return this.state.mode === "display"
	}

	inEditMode() {
		return this.state.mode === "edit"
	}

	openEditor() {
		this.setState({ mode: "edit" })
	}

	closeEditor() {
		this.setState({ mode: "display" })
	}

	changeEditorInput(event, value) {
		this.setState({
			editor: {
				input: value
			}
		})
	}

	onSubmit(event) {
		event.preventDefault()
		this.props.websocket.setUsername(this.state.editor.input)
		this.closeEditor()
	}
}

export default UsernameChanger;