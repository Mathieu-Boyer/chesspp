<script setup>
import Board from '../components/Board.vue';

</script>

<template>
    <div class="gamePage">
        <Board></Board>
    </div>

</template>

<style scoped>
.gamePage{
    height: 100vh;
    display: flex;
    align-items: center;
    justify-content: center;
    flex-direction: column;
}
</style>
