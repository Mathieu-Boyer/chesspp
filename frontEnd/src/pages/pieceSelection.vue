<script setup>
import { Card } from 'primevue';
import { ref } from 'vue';

const pieces = ref([
    {
        title : "The Queen",
        img : "/chessPieces/White/queen.png"
    },
    {
        title : "The Prince",
        img : "/chessPieces/White/prince.png"
    },
    {
        title : "The Chameleon",
        img : "/chessPieces/White/cameleon.png"
    }
])
</script>

<template>
    <div class="selectionPage">

        <h2>Select your piece for this game</h2>

        <div class="cardContainer">
            <Card class="card" v-for="piece in pieces" :key="piece.title">
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
