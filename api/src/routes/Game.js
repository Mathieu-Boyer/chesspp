import { Router } from "express"
import db from "../models/index.js"
import { authenticate } from "../middlewares/jwt.js";
import { Op } from "sequelize";
import { sendToUser } from "../utils/sockets.js";
import { drawIsOffered, gameIsNotFinished, notDrawProposer, playerIsInTheGame } from "../utils/guards.js";

import { execFile } from "child_process";
import { loadGameById, loadGamePlayers } from "../middlewares/games.js";

const {or} = Op;
const router = Router();

router.get('/', authenticate, async (req, res)=>{
    const foundGames = await db.Games.findAll({
        where: {
            [or]: [
                {whitePlayerId : req.id},
                {blackPlayerId : req.id}
            ]
        },
        include: [
            { model: db.Users, as: 'whitePlayer' },
            { model: db.Users, as: 'blackPlayer' },
            { model: db.Users, as: 'winner' },
            { model: db.Users, as: 'drawProposer' },
        ]
});

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
        },
        include: [
            { model: db.Users, as: 'whitePlayer' },
            { model: db.Users, as: 'blackPlayer' },
            { model: db.Users, as: 'winner' },
            { model: db.Users, as: 'drawProposer' },
        ]
});

    if (!foundGames)
        return res.status(404).json({message : "No games were found."});

    return res.status(200).json({games : foundGames});
})

router.get('/:id', authenticate, async (req, res)=>{
    const id = req.params.id;

    if (!id)
        return res.status(400).json({message : "A game id must be provided to use this endpoint."});
    const foundGame = await db.Games.findOne(
        {
            where: {id},
            include: [
                { model: db.Users, as: 'whitePlayer' },
                { model: db.Users, as: 'blackPlayer' },
                { model: db.Users, as: 'winner' },
                { model: db.Users, as: 'drawProposer' },
            ]
        });
    if (!foundGame)
        return res.status(404).json({message : "No game with this ID was found."});

    return res.status(200).json({game : foundGame});
})

router.put('/:id/move', authenticate, loadGameById, loadGamePlayers ,  async (req, res)=>{
    const id = req.gameId;

    if (!id)
        return res.status(400).json({message : "A game id must be provided to use this endpoint."});
    let body = req.body;

    if (!body || !body.move)
        return res.status(400).json({message : "You must provide a move."});

    let foundGame = req.foundGame;

    console.log(req.id, foundGame.whitePlayer.id, foundGame.colorToPlay);
    if (((req.id == foundGame.whitePlayer.id) && foundGame.colorToPlay != "White") || ((req.id == foundGame.blackPlayer.id) && foundGame.colorToPlay != "Black"))
        return res.status(400).json({message : "It's not your turn to play."});

    console.log(foundGame.fenList[foundGame.fenList.length - 1])
    execFile('../chessEngine/app', [body.move, foundGame.fenList[foundGame.fenList.length - 1]], async (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${error.message}`);
            return;
        }
        if (stderr) {
            console.log("huuuuuh", stderr)
            res.status(400).json({message : stderr});
            return;
        }

        try {
    console.log("huuuuuh0")
            
            let json = JSON.parse(stdout);
            console.log(json, body.move);



            if (body.move.length > 2){
                foundGame.fenList = [...foundGame.fenList, json.new_FEN.trim()];
                foundGame.moveList = [...foundGame.moveList, json.applied_move];
                foundGame.colorToPlay = (foundGame.colorToPlay == "White" ? "Black" : "White");
            }
            else if (body.move.length == 2){
                console.log(json.allowed_move)
                sendToUser(req.id, "game:update", {lastFen : foundGame.fenList[foundGame.fenList.length - 1], allowed_moves : json.allowed_move})
                return res.status(200).json("sucess");
            }



            if (json.game_status != 0){
                foundGame.status = "finished";
                foundGame.winnerId = req.id;
            }
        console.log("huuuuuh1")

            await foundGame.save();
            await foundGame.reload({
            include: [
                { model: db.Users, as: 'whitePlayer' },
                { model: db.Users, as: 'blackPlayer' },
                { model: db.Users, as: 'winner' },
                { model: db.Users, as: 'drawProposer' },
            ]})

    console.log("huuuuuh2")



    sendToUser(foundGame.blackPlayerId, "game:update", {game: foundGame, status : json.game_status})
    sendToUser(foundGame.whitePlayerId, "game:update", {game: foundGame, status : json.game_status})

    res.status(200).json({game : foundGame});

        } catch (e) {
            return res.status(400).json({message : e});
        }
    });



})

router.patch("/:id/resign", authenticate, async (req, res)=>{
    const id = req.params.id;

    if (!id)
        return res.status(400).json({message : "A game id must be provided to use this endpoint."});


    let foundGame = await db.Games.findOne(
        {
            where: {id},
            include: [
                { model: db.Users, as: 'whitePlayer' },
                { model: db.Users, as: 'blackPlayer' },
                { model: db.Users, as: 'winner' },
                { model: db.Users, as: 'drawProposer' },
            ]
        });

    if (!foundGame)
        return res.status(404).json({message : "No game with this ID was found."});

    try {
        gameIsNotFinished(foundGame);
        playerIsInTheGame(req.id, foundGame)
    } catch (error) {
        console.log(error, "aaaah okay")
        return res.status(401).json(error);
    }

    foundGame.status = "finished";
    if (req.id == foundGame.blackPlayerId)
        foundGame.winnerId = foundGame.whitePlayerId;
    else
        foundGame.winnerId = foundGame.blackPlayerId;

    await foundGame.save();
    await foundGame.reload({
        include: [
            { model: db.Users, as: 'whitePlayer' },
            { model: db.Users, as: 'blackPlayer' },
            { model: db.Users, as: 'winner' },
            { model: db.Users, as: 'drawProposer' },
        ]
    });

    sendToUser(foundGame.blackPlayerId, "game:finished", {game: foundGame})
    sendToUser(foundGame.whitePlayerId, "game:finished", {game: foundGame})

    return res.status(200).json({game : foundGame});
})

router.patch("/:id/draw/offer", authenticate , async (req, res)=>{
    const id = req.params.id;

    if (!id)
        return res.status(400).json({message : "A game id must be provided to use this endpoint."});

    let foundGame = await db.Games.findOne(
        {
            where: {id},
            include: [
                { model: db.Users, as: 'whitePlayer' },
                { model: db.Users, as: 'blackPlayer' },
                { model: db.Users, as: 'winner' },
                { model: db.Users, as: 'drawProposer' },
            ]
        });

    if (!foundGame)
        return res.status(404).json({message : "No game with this ID was found."});

    try {
        gameIsNotFinished(foundGame);
        playerIsInTheGame(req.id, foundGame);
    } catch (error) {
        return res.status(401).json(error);
    }

    foundGame.drawProposerId = req.id;

    await foundGame.save();
    await foundGame.reload({
        include: [
            { model: db.Users, as: 'whitePlayer' },
            { model: db.Users, as: 'blackPlayer' },
            { model: db.Users, as: 'winner' },
            { model: db.Users, as: 'drawProposer' },
        ]
    });
    const opponent =  req.id == foundGame.blackPlayerId ? foundGame.whitePlayerId : foundGame.blackPlayerId;

    sendToUser(opponent , "game:draw" , {message : `${foundGame.drawProposer.username} offered you a draw.`})
    return res.status(200).json({game : foundGame});
})

router.patch("/:id/draw/accept", authenticate , async (req, res)=>{
    const id = req.params.id;

    if (!id)
        return res.status(400).json({message : "A game id must be provided to use this endpoint."});

    let foundGame = await db.Games.findOne(
        {
            where: {id},
            include: [
                { model: db.Users, as: 'whitePlayer' },
                { model: db.Users, as: 'blackPlayer' },
                { model: db.Users, as: 'winner' },
                { model: db.Users, as: 'drawProposer' },
            ]
        });

    if (!foundGame)
        return res.status(404).json({message : "No game with this ID was found."});

    try {
        gameIsNotFinished(foundGame);
        playerIsInTheGame(req.id, foundGame);
        notDrawProposer(req.id, foundGame);
        drawIsOffered(foundGame);
    } catch (error) {
        console.log(error)
        return res.status(401).json(error);
    }

    foundGame.status = "finished"

    await foundGame.save();
    await foundGame.reload({
        include: [
            { model: db.Users, as: 'whitePlayer' },
            { model: db.Users, as: 'blackPlayer' },
            { model: db.Users, as: 'winner' },
            { model: db.Users, as: 'drawProposer' },
        ]
    });
    
    sendToUser(foundGame.blackPlayerId, "game:finished", {game: foundGame})
    sendToUser(foundGame.whitePlayerId, "game:finished", {game: foundGame})

    return res.status(200).json({game : foundGame});
})

router.patch("/:id/draw/decline", authenticate , async (req, res)=>{
    const id = req.params.id;

    if (!id)
        return res.status(400).json({message : "A game id must be provided to use this endpoint."});

    let foundGame = await db.Games.findOne(
        {
            where: {id},
            include: [
                { model: db.Users, as: 'whitePlayer' },
                { model: db.Users, as: 'blackPlayer' },
                { model: db.Users, as: 'winner' },
                { model: db.Users, as: 'drawProposer' },
            ]
        });

    if (!foundGame)
        return res.status(404).json({message : "No game with this ID was found."});

    try {
        gameIsNotFinished(foundGame);
        playerIsInTheGame(req.id, foundGame);
        notDrawProposer(req.id, foundGame);
        drawIsOffered(foundGame);
    } catch (error) {
        return res.status(401).json(error);
    }


    foundGame.drawProposerId = null;

    await foundGame.save();
    await foundGame.reload({
        include: [
            { model: db.Users, as: 'whitePlayer' },
            { model: db.Users, as: 'blackPlayer' },
            { model: db.Users, as: 'winner' },
            { model: db.Users, as: 'drawProposer' },
        ]
    });
    
    const opponent =  req.id == foundGame.blackPlayerId ? foundGame.whitePlayerId : foundGame.blackPlayerId;

    sendToUser(opponent , "game:draw" ,  {message: "Your opponent declined the draw.", game: foundGame})

    return res.status(200).json({game : foundGame});
})

export default router;