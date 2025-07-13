export const gameIsNotFinished = (game)=>{
    if (game.status == "finished")
        throw "No modifications can be done to this game, it is already finished.";
}


export const playerIsInTheGame = (playerId, game)=>{
    if (playerId != game.whitePlayerId && playerId != game.blackPlayerId)
        throw "You are not in this game.";
}

export const notDrawProposer = (playerId, game)=>{
    if (game.drawProposerId == playerId)
        throw "You can't accept/decline a draw by yourself.";
}

export const drawIsOffered = (game)=>{
    if (!game.drawProposerId)
        throw "You can't accept/decline a draw that was not offered in the first place.";
}