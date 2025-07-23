
import { io } from "socket.io-client";

const socket = io("http://localhost:8000", {
    autoConnect : false,
    withCredentials: false,
});

export default socket;