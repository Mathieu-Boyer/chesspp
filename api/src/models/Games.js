
export default (sequelize, DataTypes)=>{
    const Games = sequelize.define("Games",{
        whitePlayerId : {
            type: DataTypes.INTEGER,
            references : {
                model : "Users",
                key: "id",
            },
            allowNull : false,
        },
        blackPlayerId : {
            type: DataTypes.INTEGER,
            references : {
                model : "Users",
                key: "id",
            },
            allowNull : false,
        },
        winnerId : {
            type: DataTypes.INTEGER,
            references : {
                model : "Users",
                key: "id",
            },
            allowNull : true,
        },
        status : {
            type: DataTypes.STRING
        },
        fenList : {
            type : DataTypes.JSON,
        },
        moveList : {
            type : DataTypes.JSON,
            allowNull : true,
        },
    })

    return Games;
}