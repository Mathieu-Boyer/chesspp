
import { io } from "socket.io-client";
// import router from "../Router";
import Game from "../utils/board/game.js";
import router from "../Router.js";
import { base, protocol } from "./api.js";

const socket = io("", {
    autoConnect : false,
    withCredentials: false,
});

export const loginSocket = async (token)=>{

    socket.auth = {token : `bearer ${token}`}
    socket.connect();
    await setupSocketListeners();
}

export const setupSocketListeners = async () => {


  socket.on('game:found', async (data) => {
    localStorage.setItem("gameState", JSON.stringify(data.game))

    localStorage.setItem("side", data.color)
    Game.updateGameInfos();
    Game.pieceSelectDeadline = Math.floor(((data.deadline - Date.now()) / 1000));

    await router.push('/game/selection').catch(err => {
  if (err.name !== 'NavigationDuplicated') {
    console.error(err)
  }
  });
  })

  socket.on('game:join', async (data) => {

    localStorage.setItem("gameState", JSON.stringify(data.game))

    Game.updateGameInfos();
    await router.push('/game').catch(err => {
        if (err.name !== 'NavigationDuplicated') {
          console.error(err, "<--");
        }
    });

    Game.drawLast();
  })
  socket.on('game:update', (data) => {
    if (data.game){
        localStorage.setItem("gameState", JSON.stringify(data.game))
        Game.updateGameInfos();
        Game.currentSelectedSquare = undefined
    }
    Game.drawLast();
    

    if (data?.game?.status == "finished"){
        // router.push("/")
        Game.dialogData.displayed = true;
        const id = localStorage.getItem("id");

        const winner = data.game.winner;
        Game.dialogData.winnerName = winner?.username;

        if (winner?.id == id)
            Game.dialogData.color = "green";
        else 
            Game.dialogData.color = "red";

        Game.dialogData.title = winner?.username + " won"; 

        if (!winner){
            Game.dialogData.color = "grey";
            Game.dialogData.title = "Draw";
        }
        

        localStorage.removeItem("gameState")
        localStorage.removeItem("side")

    }
    if (data.allowed_moves){
        Game.drawDots(data.allowed_moves);
        return;
    }
  })
}

export const removeSocketListeners = () =>{
  socket.off('game:found')
  socket.off('game:update')
  socket.off('game:join')
}

export default socket;