import db from "../models/index.js";


export const loadGameById = async (req, res, next)=>{
    req.gameId = req.params.id;
    let foundGame = await db.Games.findOne(
        {
            where: {id : req.gameId},
            include: [
                { model: db.Users, as: 'whitePlayer' },
                { model: db.Users, as: 'blackPlayer' },
                { model: db.Users, as: 'winner' },
                { model: db.Users, as: 'drawProposer' },
            ]
    });

    req.foundGame = foundGame;
    
    next();
}


export const loadGamePlayers = async (req, res, next)=>{
    if (!req.foundGame)
        res.status(400).json({message : "No game was found"})

    let foundGame = req.foundGame;
    req.whitePlayer = foundGame.whitePlayer;
    req.blackPlayer = foundGame.blackPlayer;
    next();
}