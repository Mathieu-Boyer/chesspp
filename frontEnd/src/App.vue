<script setup lang="ts">
import { Suspense } from 'vue';
import { RouterView } from 'vue-router'

</script>
<template>

<Suspense>
    <template #default>
      <RouterView />
    </template>
    <template #fallback>
      <div>...loading</div>
    </template>
</Suspense>

</template>

<style scoped>

</style>