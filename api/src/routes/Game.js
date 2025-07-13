import { Router } from "express"
import db from "../models/index.js"
import { authenticate } from "../middlewares/jwt.js";
import { Op } from "sequelize";


const {or} = Op;
const router = Router();

router.get('/', authenticate, async (req, res)=>{
    const foundGames = await db.Games.findAll({
        where: {
        [or]: [
            {whitePlayerId : req.id},
            {blackPlayerId : req.id}
        ]
    }});

    if (!foundGames)
        return res.status(404).json({message : "No games were found."});

    return res.status(200).json({games : foundGames});
})

router.get('/of/:id', authenticate, async (req, res)=>{
    const id = req.params.id;
    if (!id)
        return res.status(400).json({message : "A user id must be provided to use this endpoint."});
    if (!await db.Users.findOne({where: {id}}))
        return res.status(400).json({message : "No user with this ID was found."});
    const foundGames = await db.Games.findAll({
        where: {
        [or]: [
            {whitePlayerId : id},
            {blackPlayerId : id}
        ]
    }});

    if (!foundGames)
        return res.status(404).json({message : "No games were found."});

    return res.status(200).json({games : foundGames});
})

router.get('/:id', authenticate, async (req, res)=>{
    const id = req.params.id;

    if (!id)
        return res.status(400).json({message : "A game id must be provided to use this endpoint."});
    const foundGame = await db.Games.findOne({where: { id }});
    if (!foundGame)
        return res.status(404).json({message : "No game with this ID was found."});

    return res.status(200).json({game : foundGame});
})

export default router;