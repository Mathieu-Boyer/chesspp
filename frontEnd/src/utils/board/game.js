import axios from "axios";
import { pieceTranslator, chessBoard, chessBoardReverse } from "./statics";


function isLowerCase(char) {
    return char === char.toLowerCase() && char !== char.toUpperCase();
}


class Game {
    constructor() {
        this.allowed_moves = [];
        this.gameInfos = JSON.parse(localStorage?.getItem("gameState"));
        this.side = localStorage?.getItem("side");
        this.canvas = null;
        this.ctx = null;
        this.piecesImages = new Map();
        this.clientWidth = 0;
        this.clientHeight = 0;
        this.scale = window.devicePixelRatio || 1;
        this.size = 0;
        this.squareSize = 0;
        this.boardIsReversed = false;
        this.width = 0;
        this.height = 0;
        this.currentSelectedSquare;
         

    }

    updateGameInfos(){
        this.gameInfos = JSON.parse(localStorage?.getItem("gameState"));
    }

    async init(canvas, errDiv, dock) {

        this.dock = await dock;
        this.canvas = canvas;
        this.errDiv = errDiv;
        this.ctx = canvas.getContext("2d");
        this.clientWidth = canvas.clientWidth;
        this.clientHeight = canvas.clientHeight;
        this.size = Math.min(this.clientWidth, this.clientHeight);
        this.squareSize = this.size / 8;
        
        this.width = this.size * this.scale;
        this.height = this.size * this.scale;
        
        canvas.width = this.width;
        canvas.height = this.height;
        canvas.style.width = this.size + 'px';
        canvas.style.height = this.size + 'px';
        
        this.ctx.scale(this.scale, this.scale);

        canvas.addEventListener('click', (e)=>this.getPressedSquare(e))
        await this.loadAllPiecesImages()
    }

    async loadAllPiecesImages() {
        const allPieces = ["rook", "knight", "bishop", "queen", "king", "pawn"];
        const colors = ["White", "Black"];
        const promises = [];
        
        for (const color of colors) {
            for (const piece of allPieces) {
                const promise = new Promise((resolve, reject) => {
                    const img = new Image();
                    img.onload = () => resolve();
                    img.onerror = () => reject(new Error(`Failed to load ${color} ${piece}`));
                    img.src = `chessPieces/${color}/${piece}.png`;
                    this.piecesImages.set(color + piece, img);
                });
                promises.push(promise);
            }
        }

        try {
            await Promise.all(promises);
            console.log('All chess pieces loaded successfully');
        } catch (error) {
            console.error('Error loading chess pieces:', error);
            throw error;
        }
    }

    drawPieceOn(row, col, pieceColor, pieceName) {
        const piece = this.piecesImages.get(pieceColor + pieceName);
        if (piece) {
            this.ctx.drawImage(
                piece, 
                col * this.squareSize, 
                row * this.squareSize, 
                this.squareSize, 
                this.squareSize
            );
        } else {
            console.warn(`Piece not found: ${pieceColor}${pieceName}`);
        }
    }

    isLowerCase(char) {
        return char === char.toLowerCase();
    }

    drawRow(fenRow, rowNum) {
        let col = 0;
        for (const char of fenRow) {
            if (!isNaN(char)) {
                // Skip empty squares
                col += parseInt(char);
                continue;
            }
            
            const pieceColor = this.isLowerCase(char) ? "Black" : "White";
            const pieceName = pieceTranslator[char.toLowerCase()];
            
            if (pieceName) {
                this.drawPieceOn(rowNum, col, pieceColor, pieceName);
            }
            col++;
        }
    }

    drawChessBoardUsingFen(fenGameState) {
        this.clearBoard();
        this.drawChessSquares();

        console.log(fenGameState)
        
        const mySide = this.getMySide();

        console.log(mySide)
        const informations = fenGameState.split(" ");
        const rows = informations[0].split("/");

        if (mySide === "White") {
            for (let i = 0; i < 8; i++) {
                this.drawRow(rows[i], i);
            }
        } else {
            for (let i = 0; i < 8; i++) {
                this.drawRow(rows[i].split("").reverse().join(""), 7 - i);
            }
        }
    }

    getMySide() {
        try {
            return localStorage?.getItem("side") || "White";
        } catch {
            return "White";
        }
    }

    drawMyPieces() {
        let pieceOrder = ["rook", "knight", "bishop", "queen", "king", "bishop", "knight", "rook"];
        let color = "White";
        let backRow = 7;
        let pawnRow = 6;
        
        if (this.boardIsReversed) {
            pieceOrder = [...pieceOrder].reverse();
            color = "Black";
            backRow = 0;
            pawnRow = 1;
        }

        for (let i = 0; i < 8; i++) {
            this.drawPieceOn(backRow, i, color, pieceOrder[i]);
            this.drawPieceOn(pawnRow, i, color, "pawn");
        }
    }

    drawChessSquares() {
        const colors = ["#EBECD0", "#739552"];
        for (let i = 0; i < 8; i++) {
            for (let j = 0; j < 8; j++) {
                this.ctx.fillStyle = colors[(i + j) % 2];
                this.ctx.fillRect(
                    j * this.squareSize, 
                    i * this.squareSize, 
                    this.squareSize, 
                    this.squareSize
                );
            }
        }
    }

    drawEnemyPieces() {
        let pieceOrder = ["rook", "knight", "bishop", "queen", "king", "bishop", "knight", "rook"];
        let color = "Black";
        let backRow = 0;
        let pawnRow = 1;
        
        if (this.boardIsReversed) {
            pieceOrder = [...pieceOrder].reverse();
            color = "White";
            backRow = 7;
            pawnRow = 6;
        }
        
        for (let i = 0; i < 8; i++) {
            this.drawPieceOn(backRow, i, color, pieceOrder[i]);
            this.drawPieceOn(pawnRow, i, color, "pawn");
        }
    }

    drawCompleteBoard() {
        this.drawChessSquares();
        this.drawMyPieces();
        this.drawEnemyPieces();
    }

    setBoardOrientation(reversed) {
        this.boardIsReversed = reversed;
    }

    clearBoard() {
        console.log(this.size, this.size)
        this.ctx.clearRect(0, 0, this.size, this.size);
    }

    resize(newSize) {
        this.size = newSize;
        this.squareSize = newSize / 8;
        this.width = newSize * this.scale;
        this.height = newSize * this.scale;
        
        this.canvas.width = this.width;
        this.canvas.height = this.height;
        this.canvas.style.width = newSize + 'px';
        this.canvas.style.height = newSize + 'px';
        
        this.ctx.scale(this.scale, this.scale);
    }

    drawDot(square) {
        let x = Math.floor(square % 8);
        let y = Math.floor(square / 8);

        let dotSize = 10;
        this.ctx.beginPath(); 
        this.ctx.fillStyle = "#232323fb"
        this.ctx.arc(x * this.squareSize + (this.squareSize / 2),
                y * this.squareSize + (this.squareSize / 2), 
                dotSize, 0, 2 * Math.PI, false);
        this.ctx.fill();
        this.ctx.closePath();
    }

    async getPressedSquare(e){
        console.log(this.canvas)
        const rect = this.canvas.getBoundingClientRect();
        const x = e.clientX - rect.left;
        const y = e.clientY - rect.top;

        console.log(x, y);
        const xSquare = Math.floor(((x / this.squareSize) % 8));
        const ySquare =  Math.floor(((y / this.squareSize) % 8));

        if (!this.currentSelectedSquare)
            this.currentSelectedSquare = this.side == "White" ? chessBoard[xSquare + (8 * ySquare)] :  chessBoard[(7 - xSquare + (8 * (7- ySquare)))];
        else
            this.currentSelectedSquare += "-" + (this.side == "White" ? chessBoard[xSquare + (8 * ySquare)] : chessBoard[(7 - xSquare + (8 * (7- ySquare)))]);
        try{
            console.log(this.currentSelectedSquare)
            let response = await axios.put(`http://localhost:8000/api/v1/games/${this.gameInfos.id}/move`, {
                move : this.currentSelectedSquare
            })

            console.log(response)

 
        }catch (err){
            console.log(err.response)
            if (err.response.data.message.trim() == "A pawn on the end of a board must provide the piece it wants to become.")
                return this.dockAppear()
            console.log(err.response.data.message)
            this.currentSelectedSquare = undefined;

            this.errDiv.innerText = err.response.data.message;
            this.drawLast();
        }
    }


    drawDots (moves){
        moves?.forEach((move, i)=>{

            if (this.side == "White")
                this.drawDot(move)
            else 
                this.drawDot(63 - move)
        })
    }


    drawLast(){
        console.log("drawing .. : ", this.gameInfos.fenList[this.gameInfos.fenList.length - 1])
        this.drawChessBoardUsingFen(this.gameInfos.fenList[this.gameInfos.fenList.length - 1])
    }

    async handleDockClick(e){
        console.log(e.target.alt)
        this.currentSelectedSquare += "=" + e.target.alt;
        try{
            let response = await axios.put(`http://localhost:8000/api/v1/games/${this.gameInfos.id}/move`, {
                move : this.currentSelectedSquare
            })
            console.log(response)
        }catch (err){
            console.log(err.response.data.message)
            this.currentSelectedSquare = undefined;
            this.errDiv.innerText = err.response.data.message;
            this.drawLast();
        }
        this.dockDissappear();
    }

    dockAppear(){
        Object.assign(this.dock.style, {
            visibility: 'visible',
        })
    }

    dockDissappear(){
        Object.assign(this.dock.style, {
            visibility: 'hidden',
        })
    }
}


export default new Game