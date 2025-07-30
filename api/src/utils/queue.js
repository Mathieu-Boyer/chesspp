import db from "../models/index.js";
import { userSelectionTimeout } from "../server.js";
import { sendToUser } from "./sockets.js";


export const autoSelectQueen = async (playerId, gameId) => {
    const foundGame = await db.Games.findOne({
        where: { id: gameId },
        include: [
        { model: db.Users, as: 'whitePlayer' },
        { model: db.Users, as: 'blackPlayer' },
        { model: db.Users, as: 'winner' },
        { model: db.Users, as: 'drawProposer' },
        ]
    });

    if (!foundGame) return;

    const isBlack = playerId === foundGame.blackPlayer.id;
    const isWhite = playerId === foundGame.whitePlayer.id;

    if (!isBlack && !isWhite) return;

    if (isBlack && foundGame.blackSelectedPiece === "-") {
        foundGame.blackSelectedPiece = "q";
    } else if (isWhite && foundGame.whiteSelectedPiece === "-") {
        foundGame.whiteSelectedPiece = "Q";
    }

    await foundGame.save();

    const updatedGame = await db.Games.findOne({
        where: { id: gameId },
        include: [
        { model: db.Users, as: 'whitePlayer' },
        { model: db.Users, as: 'blackPlayer' },
        { model: db.Users, as: 'winner' },
        { model: db.Users, as: 'drawProposer' },
        ]
    });

    const white = updatedGame.whiteSelectedPiece;
    const black = updatedGame.blackSelectedPiece;

    const bothSelected = white !== "-" && black !== "-";
    const stillSelecting = updatedGame.status === "selection";

    if (bothSelected && stillSelecting) {
        updatedGame.status = "active";
        updatedGame.fenList = [`rnb${black}kbnr/pppppppp/8/8/8/8/PPPPPPPP/RNB${white}KBNR w KQkq - 0 1 - ${black}=;${white}=`];
        await updatedGame.save();

        sendToUser(updatedGame.whitePlayer.id, "game:join", { game: updatedGame });
        sendToUser(updatedGame.blackPlayer.id, "game:join", { game: updatedGame });
    } else {
        sendToUser(playerId, "game:partial-selection", { game: updatedGame });
    }
    userSelectionTimeout.delete(playerId);
};