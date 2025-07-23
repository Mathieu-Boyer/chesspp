<script setup>
import { Button } from 'primevue';
import Loader from '../components/loader.vue';
import { quitQueue } from '../utils/queue';
</script>

<template>
    <div class="queuePage">
        <Loader></Loader>
        <Button @click="quitQueue" label="cancel the search" ></Button>
    </div>
</template>

<style scoped>
.queuePage{
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    height: 100vh;
    gap: 2rem;
}
h2{
  font-size: 2rem;
}

</style>
