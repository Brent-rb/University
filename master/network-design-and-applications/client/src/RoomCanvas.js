import React, { Component } from 'react';
import Paper from 'material-ui/Paper';
import RaisedButton from 'material-ui/RaisedButton';
import Subheader from 'material-ui/Subheader';
import FlatButton from 'material-ui/FlatButton';

import './RoomCanvas.css';

class RoomCanvas extends Component {
	localCanvas = {
		canvas: null,
		drawing: false,
		lastCords: {
			xN: 0,
			xY: 0
		},
		lastUpdate: 0,
		maxWidth: 640,
		maxHeight: 640,
		lineWidth: 3,
	}

	state = {
		buttonStates: {
			startEnabled: true,
			endEnabled: true,
		}
	}	

	constructor(props) {
		super(props)

		this.mouseMove = this.mouseMove.bind(this)
		this.updateDraw = this.updateDraw.bind(this)

		this.clearCanvas = this.clearCanvas.bind(this)
		this.resizeCanvas = this.resizeCanvas.bind(this)
		this.rescaleCanvas = this.rescaleCanvas.bind(this)

		this.onCanvasMouseDown = this.onCanvasMouseDown.bind(this)
		this.onCanvasMouseUp = this.onCanvasMouseUp.bind(this)
		this.onCanvasMouseMove = this.onCanvasMouseMove.bind(this)

		this.startGame = this.startGame.bind(this)
		this.endGame = this.endGame.bind(this)

		this.onGameUpdate = this.onGameUpdate.bind(this)

		this.localCanvas.ratio = this.localCanvas.maxWidth / this.localCanvas.maxHeight
	}

	componentWillMount() {
		this.props.websocket.addCallback("mouse-move", this.mouseMove)
		this.props.websocket.addCallback("update-draw", this.updateDraw)
		this.props.websocket.addCallback("canvas-clear", this.clearCanvas)
	}

	componentDidMount() {
		window.addEventListener("resize", this.rescaleCanvas)

		this.localCanvas.canvas = this.refs.drawing_canvas.getContext('2d')
		this.localCanvas.canvas.fillStyle = 'black'
		this.localCanvas.canvas.lineWidth = this.localCanvas.lineWidth
		this.resizeCanvas()
		this.rescaleCanvas()
	}

	componentWillUnmount() {
		this.props.websocket.removeCallback("mouse-move", this.mouseMove)
		this.props.websocket.removeCallback("update-draw", this.updateDraw)
		this.props.websocket.removeCallback("canvas-clear", this.clearCanvas)

		window.removeEventListener("resize", this.rescaleCanvas)
	}

	render() {
		return (
			<Paper className="Room-pictionary-canvas-container">
				<Subheader>Canvas</Subheader>
				<div className="Room-pictionary-canvas-wrapper">
					<canvas id="paper" ref="drawing_canvas" width="200px" height="200px"
						onMouseMove={this.onCanvasMouseMove}
						onMouseDown={this.onCanvasMouseDown}
						onMouseUp={this.onCanvasMouseUp}
						onMouseLeave={this.onCanvasMouseUp}
					></canvas>
				</div>
				<div className="Room-pictionary-canvas-buttons">
					<FlatButton className="Room-game-button" label="Start game" primary={true}
						disabled={!this.state.buttonStates.startEnabled} onClick={this.startGame} />
					<FlatButton className="Room-game-button" label="End game" primary={false}
						disabled={!this.state.buttonStates.endEnabled} onClick={this.endGame} />
				</div>
			</Paper>
		)
	}

	clearCanvas() {
		var canvasItself = this.localCanvas.canvas.canvas
		this.localCanvas.canvas.clearRect(0, 0, canvasItself.width, canvasItself.height)
	}

	resizeCanvas() {
		var canvas = this.localCanvas.canvas.canvas
		canvas.width = this.localCanvas.maxWidth
		canvas.height = this.localCanvas.maxHeight
		this.localCanvas.canvas.lineWidth = this.localCanvas.lineWidth
	}

	rescaleCanvas() {
		var canvas = this.localCanvas.canvas.canvas
		var parent = canvas.parentNode
		var parentWidth = parent.clientWidth
		var parentHeigth = parent.clientHeight

		var width = parentWidth
		var height = Math.floor(parentWidth / this.localCanvas.ratio)
		if(height > parentHeigth) {
			var width = Math.floor(parentHeigth * this.localCanvas.ratio)
			height = parentHeigth
		}

		canvas.style.width = "" + width + "px"
		canvas.style.height = "" + height + "px"
	}

	getCanvasCords(mouseEvent) {
		var canvas = this.localCanvas.canvas.canvas
		var rect = canvas.getBoundingClientRect();
		return {
			x: ((mouseEvent.clientX - rect.x) / canvas.clientWidth) * canvas.width,
			y: ((mouseEvent.clientY - rect.y) / canvas.clientHeight) * canvas.height,
		}
	}

	normalizeCanvasCords(cords) {
		return {
			x: cords.x / this.localCanvas.canvas.canvas.width,
			y: cords.y / this.localCanvas.canvas.canvas.height
		}
	}

	unNormalizeCanvasCords(cords) {
		return {
			x: cords.x * this.localCanvas.canvas.canvas.width,
			y: cords.y * this.localCanvas.canvas.canvas.height
		}
	}

	onCanvasMouseDown(e) {
		e.preventDefault()
		this.localCanvas.drawing = true
		this.localCanvas.lastCords = this.normalizeCanvasCords(this.getCanvasCords(e))
	}

	onCanvasMouseUp(e) {
		e.preventDefault()
		this.localCanvas.drawing = false
	}

	onCanvasMouseMove(e) {
		e.preventDefault()
		var currentMilli = (new Date()).getTime()
		var currentCords = this.getCanvasCords(e)
		console.log(currentCords)
		var currentCordsN = this.normalizeCanvasCords(currentCords)

		// Send updates every 30 milliseconds
		if (currentMilli - this.localCanvas.lastUpdate > 30) {
			if (this.localCanvas.drawing) {
				// Send draw update event
				this.props.websocket.sendDrawUpdate(this.props.user.id, this.localCanvas.lastCords, currentCordsN)
				this.localCanvas.lastCords = currentCordsN
			} else {
				// Send mouse update event
				this.props.websocket.sendMouseMove(this.props.user.id, currentCordsN)
			}

			this.localCanvas.lastUpdate = currentMilli
		}
	}

	onGameUpdate(gameData) {
		if (gameData == null) {
			// No active game.
			this.setState({buttonStates: {
					startEnabled: true,
					endEnabled: false,
				}
			})
		} else {
			// Active game.
			this.clearCanvas()
			var currentUserId = this.props.user.id
			this.setState({buttonStates: {
					startEnabled: false,
					endEnabled: gameData.itId === currentUserId,
				}
			})
		}
	}

	mouseMove(data) {
		// 
	}

	updateDraw(data) {
		var beginCordinatesN = data.beginCordinates
		var endCordinatesN = data.endCordinates
		var beginCordinates = this.unNormalizeCanvasCords(beginCordinatesN)
		var endCordinates = this.unNormalizeCanvasCords(endCordinatesN)

		// Draw the line
		this.localCanvas.canvas.beginPath()
		this.localCanvas.canvas.moveTo(beginCordinates.x, beginCordinates.y)
		this.localCanvas.canvas.lineTo(endCordinates.x, endCordinates.y)
		this.localCanvas.canvas.stroke()
	}

	startGame(e) {
		this.props.websocket.sendStartGame()
	}

	endGame(e) {
		this.props.websocket.sendStopGame()
	}
}

export default RoomCanvas;
