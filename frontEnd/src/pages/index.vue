<script setup>
import Loader from '../components/loader.vue';
import Button from "primevue/button"

import { joinQueue } from '../utils/queue';

</script>

<template>
    <div class="indexPage">
        <Button @click="joinQueue" label="Join queue"></Button>
    </div>
</template>

<style scoped>

    .indexPage {
        display: flex;
        justify-content: center ;
        align-items: center ;
        height: 100vh;
    }
</style>
