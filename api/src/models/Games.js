
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
            type : DataTypes.ARRAY(DataTypes.STRING),
        },
        moveList : {
            type : DataTypes.ARRAY(DataTypes.STRING),
        },
    })

    return Games;
}