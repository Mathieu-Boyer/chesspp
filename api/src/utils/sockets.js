import { io, userSockets } from "../server.js"

export const sendToUser = (userId, event , data)=>{

    const socketId = userSockets.get(userId);

    if (!socketId)
        console.log("trying to send message to a user not connected on socket right now.", userSockets.size);
    
    io.to(socketId).emit(event , data);
}