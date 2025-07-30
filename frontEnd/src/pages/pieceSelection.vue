<script setup>
import axios from 'axios';
import { Card } from 'primevue';
import { ref } from 'vue';
import router from '../Router';
import game from '../utils/board/game';
import { v1 } from '../utils/api';



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

    const response = await axios.patch(`${v1}games/${game.gameInfos.id}/select`, {
        piece : elWithId.id
    })
    // router.push('/game')
    pieces.value = pieces.value.filter((card)=>card.representation == elWithId.id);
}


const handleDeadlineTimer = ref(game.pieceSelectDeadline);

setInterval(()=>{
    if (!handleDeadlineTimer.value)
        return
    handleDeadlineTimer.value -= 1;
}, 1000)

</script>

<template>
    <div class="selectionPage">

        <h2>Select your piece for this game</h2>
        <h2>{{ handleDeadlineTimer }}</h2>

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
.cardContainer {
    display: flex;
    flex-wrap: wrap;
    justify-content: center;
    gap: 2rem;
    padding: 0 1rem;
    max-width: 100%;
}

.card {
    display: flex;
    flex-direction: column;
    align-items: center;
    width: 100%;
    max-width: 300px;
    background-color: #1e1e1e;
    color: white;
    font-weight: bolder;
    cursor: pointer;
    transition: all 0.5s;
}

.card:hover {
    background-color: #303030;
    transform: translateY(-1rem);
    box-shadow: 2px 2px 20px #4f4f4f;
}

.card:active {
    transition: all 0.2s;
    transform: translateY(0);
    box-shadow: none;
}

img {
    width: 100%;
    object-fit: contain;
}

@media (min-width: 951px) {
    .selectionPage{
        display: flex;
        justify-content: center;
        align-items: center;
        flex-direction: column;
        gap: 2rem;
        width: 100%;
        min-height: 100vh;
    }

    img {
        height: 15rem;
    }

}
@media (max-width: 950px) {
    .cardContainer {
        margin-top: 2rem;
    }

    .selectionPage {
        gap: 3rem;
        padding: 1rem;
    }

    h2 {
        font-size: 1.2rem;
        text-align: center;
    }

    .card {
        max-width: 90vw;
    }

    img {
        height: 10rem;
    }
}
</style>
