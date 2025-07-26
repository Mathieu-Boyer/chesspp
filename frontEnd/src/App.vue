<script setup lang="ts">
import { Suspense } from 'vue';
import { RouterView } from 'vue-router'
import 'primeicons/primeicons.css'
import Nav from './components/Nav.vue';

</script>
<template>
<Nav></Nav>
<Suspense>
    <template #default>
      <RouterView :key="$route.fullPath" />
    </template>
    <template #fallback>
      <div>...loading</div>
    </template>
</Suspense>

</template>

<style scoped>

</style>