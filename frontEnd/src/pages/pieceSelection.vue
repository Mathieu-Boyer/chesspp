<script setup>
import axios from 'axios';
import { Card } from 'primevue';
import { ref } from 'vue';
import router from '../Router';
import game from '../utils/board/game';



const side = localStorage.getItem("side")

console.log(game.gameInfos)
const pieces = ref([
    {
        title : "The Queen",
        img : "/chessPieces/White/queen.png",
        representation : side == "White" ? "Q" : "q"
    },
    {
        title : "The Prince",
        img : "/chessPieces/White/prince.png",
        representation : side == "White" ? "S" : "s"
    },
    {
        title : "The Chameleon",
        img : "/chessPieces/White/cameleon.png",
        representation : side == "White" ? "C" : "c"
    }
])

const handleSelection = async (e)=>{

    const clickedElem = e.target;
    const elWithId = clickedElem.id ? clickedElem : clickedElem.closest('[id]');
    console.log(elWithId.id);

    const response = await axios.patch(`/api/v1/games/${game.gameInfos.id}/select`, {
        piece : elWithId.id
    })
    
    // router.push('/game')
    pieces.value = pieces.value.filter((card)=>card.representation == elWithId.id);
}
</script>

<template>
    <div class="selectionPage">

        <h2>Select your piece for this game</h2>

        <div class="cardContainer">
            <Card @click="handleSelection" class="card" v-for="piece in pieces" :key="piece.title" :id="piece.representation">
                <template #header>
                    <img :alt="piece.title" :src="piece.img" />
                </template>
                <template class="cardTitle" #title><h4>{{ piece.title }}</h4></template>
            </Card>
        </div>
    </div>
</template>

<style scoped>
.selectionPage{
    height: 100vh;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items:center ;
    gap: 5rem;
}
.cardContainer {
    display: flex;
    gap: 2rem;
}
.card {
    display: flex;
    justify-content: space-between;
    align-items: center;
    flex-direction: column;
    width: 20rem;
    background-color: #1e1e1e;
    font-weight:bolder;

    cursor: pointer;
    transition: all .5s;
}

.card:hover {
    background-color: #303030;
    transform: translateY(-1rem);
    box-shadow: 2px 2px 20px #4f4f4f;
}

.card:active{
    transition: all .2s;

    transform: translateY(0);
    box-shadow: none;
}



img{
    height: 100%;
    width: 100%;
}
</style>
