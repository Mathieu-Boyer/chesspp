<script setup>
import { Button, Avatar } from 'primevue';
import Board from '../components/Board.vue';
import axios from 'axios';
import game from '../utils/board/game';
import { v1 } from '../utils/api';
import { computed, reactive, ref } from 'vue';

async function handleResign  (e){
   const response =  await axios.patch(`${v1}games/${game.gameInfos.id}/resign`)
}

const side = localStorage.getItem("side")

const currentEnemy = ref(side == "Black" ? game.gameInfos.whitePlayer : game.gameInfos.blackPlayer)
const currentSelf = ref(side == "White" ? game.gameInfos.whitePlayer : game.gameInfos.blackPlayer)


const colorToPlay = computed(()=>game.gameInfos.colorToPlay)
console.log(currentEnemy.value, "lalalalalalalalala")
console.log(game.gameInfos.colorToPlay , side)


</script>

<template>
    <div class="gamePage">

        <div class="boardContainer">

            <div class="playerInfos" :class="colorToPlay != side ? 'underline' : ''">
                <Avatar :image="'/avatars/' + currentEnemy.avatar"></Avatar>
                <h3>{{ currentEnemy.username }}</h3>
            </div>
            <Board></Board>
            <div class="playerInfos" :class="colorToPlay == side ? 'underline' : ''">
                <Avatar :image="'/avatars/' + currentEnemy.avatar"></Avatar>
                <h3>{{ currentSelf.username }}</h3>

                <div class="btns">
                    <Button @click="handleResign" class="resignButton" label="resign" severity="danger" ></Button>
                </div>
            </div>


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

.boardContainer{
    position: relative;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    width: 100%;
    gap: 1rem;
}

.playerInfos {
    display: flex;
    align-items: center;
    gap: 1rem;
}

.underline h3{
    position: relative;
}
.underline h3::after{
    content: "";
    position: absolute;
    bottom: 0;
    left: 0;
    width: 100%;
    height: 3px;
    background-color: #739552;
    border-radius: 20rem;
}
</style>
