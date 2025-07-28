import express from 'express'
import db from './models/index.js';
import auth from './routes/Auth.js';
import userSelf from './routes/UserSelf.js';
import user from './routes/User.js';
import queue from './routes/Queue.js';
import game from './routes/Game.js';
import { authenticate, authenticateSocket } from './middlewares/jwt.js';
import { checkRole } from './middlewares/roles.js';
import { createServer } from "http"
import { Server } from "socket.io"
import path from 'path';
import cors from "cors"
import { Op } from 'sequelize';
import { fileURLToPath } from 'url';



const app = express();
const httpServer = createServer(app);
app.use(express.json())
app.use(cors());
export const io = new Server(httpServer, {
  cors: {
    origin: 'http://localhost:5173',
    methods: ['GET', 'POST' , 'PUT', 'PATCH', 'DELETE'],
    credentials: true
  }
});
export let userSockets = new Map()


io.use(authenticateSocket)

io.on("connection", (socket)=>{
    userSockets.set(socket.userId, socket.id);

    socket.on("disconnect", ()=>{
        userSockets.delete(socket.userId);
        console.log("new userSockets size : ", userSockets.size);
    })
})

httpServer.listen(8000, ()=>{
    console.log("listening on port 8000");
})

app.use("/api/v1/auth", auth);
app.use("/api/v1/users/self", userSelf);
app.use("/api/v1/users", user);
app.use("/api/v1/queue", queue);
app.use("/api/v1/games", game);


app.post("/testing_jwt", authenticate, (req, res)=>{
    console.log(req.id , req.email, req.username, req.role)
    res.json("token passed validation !!")
});

app.post("/testing_role_protection", authenticate , checkRole("admin"), (req, res)=>{
    console.log(req.id , req.email, req.username, req.role);
    res.json("role validated !!");
});



const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

// Serve the Vue dist folder
app.use(express.static(path.join(__dirname, '../../frontEnd/dist')));

// Fallback for client-side routing (Vue Router in history mode)
app.get(/\/(?!api).*/, (req, res) => {
  res.sendFile(path.join(__dirname, '../../frontEnd/dist/index.html'));
});
try {
    // await db.Users.drop();
    // await db.Games.drop();

    // await db.sequelize.sync({ force: true })

// await sequelize.sync({ force: false });

//     await db.Users.update(
//   { avatar: 'default.png' },
//   {
//     where: {
//       [Op.or]: [
//         { avatar: null },
//         { avatar: '' }
//       ]
//     }
//   }
// );

    // await db.sequelize.sync()
    await db.sequelize.authenticate()

    console.log("Connected to DB.")

} catch (err) {
    console.error("Credential error for DB", err.message);
}
