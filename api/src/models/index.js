import { Sequelize } from 'sequelize';
import Users from './Users.js';
import Games from './Games.js';


console.log(process.env.SEQUELIZE_USER, process.env.SEQUELIZE_PWD);
const sequelize = new Sequelize("chesspp", process.env.SEQUELIZE_USER, process.env.SEQUELIZE_PWD, {
    dialect: 'mariadb'
})

export let queue = new Set();
let db = {
    sequelize,
    Sequelize,
    Users : Users(sequelize, Sequelize.DataTypes),
    Games : Games(sequelize, Sequelize.DataTypes)
}

db.Games.belongsTo(db.Users, { as: 'whitePlayer', foreignKey: 'whitePlayerId' });
db.Games.belongsTo(db.Users, { as: 'blackPlayer', foreignKey: 'blackPlayerId' });
db.Games.belongsTo(db.Users, { as: 'winner', foreignKey: 'winnerId' });
db.Games.belongsTo(db.Users, { as: 'drawProposer', foreignKey: 'drawProposerId' });

export default db