<script setup>

import { nextTick, onMounted, ref } from 'vue';
import Game from '../utils/board/game.js';
import { Dock } from 'primevue';






    function handlePromotion(e){
        console.log(e.target)
    }

    const dockRef = ref(null)

    let items = ref([]);

    const canvasRef = ref(null);
    const errDiv = ref(null);
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
        await Game.init(canvasRef.value, errDiv.value, dockRef.value?.$el)

        Game.drawLast();


    })

</script>

<template>
    <div class="boardContainer">
            <Dock ref="dockRef" class="dock" :model="items" position="top">
                <template #itemicon="{ item }">
                    <img @click="Game.handleDockClick" v-tooltip.top="item.label" :alt="item.label" :src="item.icon" style="width: 100%" />
                </template>
            </Dock>
        <canvas ref="canvasRef"></canvas>
    </div>
    <div class="error" ref="errDiv"></div>
</template>

<style scoped>


    canvas {
        height: 50rem;
        width: 50rem; 
    }

    .error {
        color: red;
    }
    .boardContainer{
        height: fit-content;
        position: relative;
        width: fit-content;
    }
    .dock{
        transform: translateY(-100%);
        visibility: hidden;
    }


    .dock img{
        cursor: pointer;

    }
</style>
