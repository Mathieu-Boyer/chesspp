import { authenticate } from "../middlewares/jwt.js";
import { queue } from "../models/index.js";
import { Router } from "express";
import db from "../models/index.js"
import { sendToUser } from "../utils/sockets.js";
import { userSelectionTimeout } from "../server.js";
import axios from "axios"
import { autoSelectQueen } from "../utils/queue.js";
const router = Router();

const SELECTION_TIME_MS = 1000000;




const matchMaking = async ()=>{
    const arrayQueue = Array.from(queue);
    const randomBoolean = Math.random() < 0.5;
    const [whitePlayer, blackPlayer] = randomBoolean ? arrayQueue : arrayQueue.reverse();
    queue.delete(whitePlayer);
    queue.delete(blackPlayer);

    try {
        const game =  await db.Games.create({
            whitePlayerId : whitePlayer,
            blackPlayerId : blackPlayer,
            status : "selection",
            winnerId : null,
            fenList : Array("rnb1kbnr/pppppppp/8/8/8/8/PPPPPPPP/RNB1KBNR w KQkq - 0 1 - Q=;q="),
            moveList : [],
            colorToPlay : "White"
        })


        const now = Date.now();
        const deadline = now + SELECTION_TIME_MS;

        userSelectionTimeout.set(whitePlayer, setTimeout(async ()=>{
            await autoSelectQueen(whitePlayer, game.id)
        }, SELECTION_TIME_MS))

        userSelectionTimeout.set(blackPlayer, setTimeout(async ()=>{
            await autoSelectQueen(blackPlayer, game.id)
        }, SELECTION_TIME_MS))

        sendToUser(whitePlayer, "game:found", {
            color : "White",
            game,
            deadline,
            message : "Your game was found."
        });
        sendToUser(blackPlayer, "game:found", {
            color : "Black",
            game,
            deadline,
            message : "Your game was found."
        });

        return game;
    } catch (error) {
        console.log(error)
    }

}

router.post("/join", authenticate, async (req, res)=>{
    // check if not already in game later when i'll have enough data, if in game notify redirection socket.
    queue.add(req.id);
    if (queue.size < 2)
        return res.status(200).json({message : "You sucessfuly joined the queue."})
    let game = await matchMaking();


    res.status(201).json({message: "Your game was found.", game})
})


router.post("/quit", authenticate, async (req, res)=>{
    queue.delete(req.id);
    res.status(200).json({message: "Queue quited successfuly."})
})

export default router;