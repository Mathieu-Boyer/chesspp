<script setup>

import { nextTick, onMounted, ref } from 'vue';
import Game from '../utils/board/game.js';
import { Button, Dialog, Dock, InputText, Tooltip } from 'primevue';
import router from '../Router.js';
import { joinQueue } from '../utils/queue.js';


    const currentGame = localStorage.getItem("gameState");

    if (!currentGame)
        router.push('/')
    const dockRef = ref(null)

    let items = ref([]);

    const canvasRef = ref(null);
    const errDiv = ref(null);
    const dialogData = ref({
        displayed : false
    })
    onMounted(async ()=>{

        items.value = [
            {
                label: `${Game.side == "White" ? 'Q' : 'q'}`,
                icon: `/chessPieces/${Game.side}/queen.png`,
            },
            {
                label: `${Game.side == "White" ? 'N' : 'n'}`,
                icon: `/chessPieces/${Game.side}/knight.png`
            },
            {
                label: `${Game.side == "White" ? 'R' : 'r'}`,
                icon: `/chessPieces/${Game.side}/rook.png`
            },
            {
                label: `${Game.side == "White" ? 'B' : 'b'}`,
                icon:  `/chessPieces/${Game.side}/bishop.png`
            }
        ];

        await nextTick();
        Game.updateGameInfos();
        await Game.init(canvasRef.value, errDiv.value, dockRef.value?.$el, dialogData.value)
        Game.drawLast();


    })


    const displayErrDivForDebug = false;
</script>

<template>
        <Dialog v-model:visible="dialogData.displayed" modal :header="dialogData.title" :style="{ width: '25rem' }" :closable="false">
                <div class="topColor" :class="dialogData.color"></div>
                <div class="buttons">
                    <Button type="button" label="Home" severity="secondary" @click="router.push('/')"></Button>
                    <Button type="button" label="Go back to queue"  @click="joinQueue(), router.push('/queue')"></Button>
                </div>
        </Dialog>
            <Dock ref="dockRef" class="dock" :model="items" position="top">
                <template #itemicon="{ item }">
                    <img @click="Game.handleDockClick" :alt="item.label" :src="item.icon" style="width: 100%" />
                </template>
            </Dock>
        <canvas ref="canvasRef"></canvas>
    <div v-if="displayErrDivForDebug" class="error" ref="errDiv"></div>
</template>

<style scoped>


    canvas {
        width: 100%;
        max-width: 40rem; 
        aspect-ratio: 1 / 1; /* Keeps it square */
        display: block;
    }

    .error {
        color: red;
    }
    .dock {
        position: absolute;
        left: 50%;
        transform: translateX(-50%);
        visibility: hidden;
    }

    .p-dock {
        border-radius: 15px;
        width: fit-content;
        background-color: #1e1e1e !important; /* replace with your preferred color */
        backdrop-filter: none !important;     /* disable blur effect if present */
        box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1); /* optional: shadow for elevation */
        border-top: 1px solid #444;           /* optional: border style */
    }

    .dock img{
        cursor: pointer;

    }

    .buttons {
        display: flex;
        gap: 1rem;
    }
    .topColor {
        position: absolute;
        top: -1px;
        left: -1px;
        height: 5px;
        width: 100.5%;
    }

    .red{
        background-color: rgb(183, 18, 18);
    }

    .green{
        background-color: #739552;
    }

    .grey{
        background-color: #636363;
    }
</style>
