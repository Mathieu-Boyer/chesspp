<script setup>
import axios from 'axios';
import { Avatar, Column, DataTable, Knob, Tag } from 'primevue';
import { ref } from 'vue';
import { useRoute } from 'vue-router'
import router from '../Router';
import { v1 } from '../utils/api';

const route = useRoute()
const userId = ref(route.params.id)


    console.log(userId)
    let user = ref(null)
    let games = ref(null)

    try {

        let id ;
        if (userId.value)
            id = userId.value
        else
            id = localStorage.getItem("id")
        const userData = await axios.get(`${v1}users/${id}`);
        const gamesData = await axios.get(`${v1}games/of/${id}`);
        user = ref(userData.data.user);
                const modifiedGames = 
            gamesData.data.games.map(game => {

                const enemy = game.whitePlayer.id == id ? game.blackPlayer : game.whitePlayer;
                let endGameType ;
                if (game.status == "finished" && id == game?.winner?.id)
                    endGameType = "win"
                else if (game.status == "finished" && id != game?.winner?.id)
                    endGameType = "lost"

                if (game.status == "finished" && !game.winner)
                    endGameType = "draw"
                return {
                ...game,
                endGameType,
                enemy
                }
            })
        games.value = modifiedGames;



        
        console.log(user.value, games.value)
    }catch(e){
        console.log(e)
        router.push('/')
    }


    user.value.avatar = "default.png"
    const winAmmount = games.value.filter(element => element.endGameType === "win").length;

    const winrate = ref(Math.floor((winAmmount/games.value.length) * 100));

    const getSeverity = (status) => {
    return status === 'win'
        ? 'success'
        : status === 'lost'
        ? 'danger'
        : status === 'draw'
        ? 'secondary'
        : null
    }


</script>

<template>

<div class="profilePage">
    <div class="profileHeader">

        <div class="profile">
            <Avatar :image="'/avatars/' + user.avatar" size="xlarge"></Avatar>
            <h2>{{ user.username }}</h2>
        </div>
        <div class="gamePlayed">
            <h3>Total games : {{ games?.length }}</h3>
        </div>
    </div>


    <div class="stats">

    <div class="knob">
        <Knob v-model="winrate" :size="200" readonly valueTemplate="{value}%"/>
        <h3>Win rate</h3>
    </div>

    <div class="tableContainer">
            <h3>Games history</h3>
            <DataTable  class="table" :value="games" size="large">
                <Column field="status" header="Status"></Column>
                <Column field="enemy.username" header="Enemy"></Column>
                <Column field="endGameType" header="Category">
                    <template #body="slotProps">
                        <Tag v-if="slotProps.data.endGameType" :value="slotProps.data.endGameType" :severity="getSeverity(slotProps.data.endGameType)" />
                    </template>
                </Column>
            </DataTable>
            </div>
    </div>
    </div>


</template>

<style scoped>
    .profilePage{
        display: flex;
        align-items: center;
        align-items: center;
        justify-content: center;
        padding: 5rem;
        flex-direction: column;
    }

    .profileHeader{
        display: flex;
        align-items: center;
        justify-content: space-between;
        padding:  2.5rem 10rem;
        width: 100%;
        flex-wrap: wrap;
        background-color: #1b1b1b;
    }

    .profile{
        display: flex;
        align-items: center;
        justify-content: center;
        gap: 1rem;
    }

    .tableContainer{
        width: 100%;
        margin-top: 1rem;
        padding: 0 4rem;

    }
    .stats{
        display: flex;
        width: 100%;
        align-items: center;
    }
    .table{
        width: 100%;
        margin-top: 1rem;
        overflow-y: scroll;
        height: 35rem;
    }
</style>
