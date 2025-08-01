
# Chess++  
**A modern twist on classic chess, real-time, multiplayer, and built from scratch in C++.**

## Try it Live  [Here](http://104.154.228.42:8000/)
Create an account and jump into a match online. (make sure to read the rules below to understand the new pieces)

---

## Key Features

### Core Gameplay
- **Full rule support**, All standard chess rules are implemented: castling, en passant, pawn promotion, and more.  
- **Custom piece variants**, At the start of each game, you're given the option to replace your queen with a custom piece or stick with the classic.
- **Real-time multiplayer**, Face off against players around the globe with smooth, live gameplay.  
- **Move validation**, A strong rules engine ensures illegal moves are caught before they happen.  

### Under the Hood
- **Custom-built engine in C++**, No frameworks or shortcuts. The entire chess logic runs on a hand-crafted C++ engine.  
- **Clean OOP architecture**, Polymorphic, designed with flexibility and maintainability in mind.  
- **Event-driven mechanics**, Piece behavior can be extended through an internal event system.  
- **Extended FEN support**, Game states are serialized using a custom FEN-based format.  
- **Full-stack integration**, C++ powers the core, with a Node.js backend and Vue3 frontend for real-time multiplayer.  
- **Cloud deployment**, Running on Google Cloud.
  
---

## Custom Pieces (2 for now)

### The Chameleon 
- **Doesn’t move on its own**, It copies.  
- **Mimics your opponent**, It can move like the last piece your opponent played (except for the king and chameleon).  
- **Evolves with each capture**, Every time it captures, it gains that piece’s movement abilities permanently.  
- **Tactical depth**, Starts off weak, but with smart play, it becomes a real threat over time.

### The Prince
- **Limited royalty**, Moves like a queen, but only up to 2 squares in any direction.  
- **Backup monarch**, If your king is checkmated and the prince is not under attack, the prince is crowned as the new king and the game continues.  
- **One-time replacement**, When the prince becomes king, the original king is removed from the board.  
- **Strategic consequence**, If the prince is captured, your king permanently loses the right to castle.

