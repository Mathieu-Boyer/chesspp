
import { io } from "socket.io-client";
// import router from "../Router";
import Game from "../utils/board/game.js";
import router from "../Router.js";

const socket = io("http://localhost:8000", {
    autoConnect : false,
    withCredentials: false,
});



// const state = reactive({
//   gameFound: null,
//   gameUpdate: null,
// })

export const loginSocket = async (token)=>{

    socket.auth = {token : `bearer ${token}`}
    socket.connect();
    await setupSocketListeners();
}

export const setupSocketListeners = async () => {

  socket.on('game:found', async (data) => {
    console.log(data)
    localStorage.setItem("gameState", JSON.stringify(data.game))
    localStorage.setItem("side", data.color)
    await router.push('/game').catch(err => {
  if (err.name !== 'NavigationDuplicated') {
    console.error(err, "meowmeowmeow");
  }
});
  })
  socket.on('game:update', (data) => {
    console.log(data)
    if (data.game){
        localStorage.setItem("gameState", JSON.stringify(data.game))
        Game.updateGameInfos();
        Game.currentSelectedSquare = undefined
    }
    Game.drawLast();
    

    if (data?.game?.status == "finished"){
        router.push("/")
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
}

export default socket;