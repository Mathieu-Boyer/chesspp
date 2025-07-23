<script setup>
import Loader from '../components/loader.vue';
import Button from "primevue/button"

import { joinQueue } from '../utils/queue';

</script>

<template>
    <Button @click="joinQueue" label="Join queue"></Button>
</template>

<style scoped>
</style>
