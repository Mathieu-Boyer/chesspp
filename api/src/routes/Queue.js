import { authenticate } from "../middlewares/jwt.js";
import { queue } from "../models/index.js";
import { Router } from "express";
import db from "../models/index.js"

const router = Router();

const matchMaking = async ()=>{
    const arrayQueue = Array.from(queue);

    const randomBoolean = Math.random() < 0.5;

    const [whitePlayer, blackPlayer] = randomBoolean ? arrayQueue : arrayQueue.reverse();


    console.log(await db.Users.findOne({where : {
        id : whitePlayer,
    }}))
    console.log(await db.Users.findOne({where : {
        id : blackPlayer,
    }}))

    queue.delete(whitePlayer);
    queue.delete(blackPlayer);


    try {
        const game =  await db.Games.create({
            whitePlayerId : whitePlayer,
            blackPlayerId : blackPlayer,
            status : "active",
            winnerId : null,
            fenList : Array("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"),
            moveList : [],
        })

        return game;
    } catch (error) {
        res.status(201).json({message: "Your game was found.", game})
    }

}

router.post("/join", authenticate, async (req, res)=>{
    // check if not already in game later, if in game notify redirection socket.
    queue.add(req.id);
    if (queue.size < 2)
        return res.status(200).json({message : "You sucessfuly joined the queue."})
    let game = await matchMaking();

    res.status(201).json({message: "Your game was found.", game})
})

export default router;