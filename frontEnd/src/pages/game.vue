<script setup>
import { Button } from 'primevue';
import Board from '../components/Board.vue';
import axios from 'axios';
import game from '../utils/board/game';


async function handleResign  (e){
   const response =  await axios.patch(`/api/v1/games/${game.gameInfos.id}/resign`)
}

</script>

<template>
    <div class="gamePage">
        <Board></Board>
        <div class="btns">
            <Button @click="handleResign" class="resignButton" label="resign" severity="danger" ></Button>
        </div>
    </div>

</template>

<style scoped>
.gamePage{
    height: 100vh;
    display: flex;
    align-items: center;
    justify-content: center;
    flex-direction: row;
    gap: 2rem;
}

.resignButton {
    color: white;
}
</style>
