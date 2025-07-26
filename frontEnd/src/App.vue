<script setup lang="ts">
import { Suspense } from 'vue';
import { RouterView } from 'vue-router'

</script>
<template>
<div class="navBar">

</div>
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
.navBar{
  display: flex;
  align-items: center;
  justify-content: center;
  width: 2rem;
  height: 100vh;
  padding: 1rem;
  background-color: rgb(22, 22, 22);
  border-right: 1px solid rgb(43, 43, 43);

  position: fixed;

}
</style>