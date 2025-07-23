
import { io } from "socket.io-client";

const socket = io("http://localhost:8000", {
    autoConnect : false,
    withCredentials: false,
});



// const state = reactive({
//   gameFound: null,
//   gameUpdate: null,
// })

export const loginSocket = (token)=>{
    socket.auth = {token : `bearer ${token}`}
    socket.connect();
    setupSocketListeners();
} 

export const setupSocketListeners = () => {
  socket.on('game:found', (data) => {
    console.log(data)
  })
  socket.on('game:update', (data) => {
    console.log(data)
  })
}

export const removeSocketListeners = () =>{
  socket.off('game:found')
  socket.off('game:update')
}

export default socket;