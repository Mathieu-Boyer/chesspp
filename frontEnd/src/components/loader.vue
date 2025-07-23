<script setup>
import { ref } from 'vue';

const allWhitePieces = [
    "/chessPieces/White/queen.png",
    "/chessPieces/White/king.png",
    "/chessPieces/White/knight.png",
    "/chessPieces/White/pawn.png",
    "/chessPieces/White/rook.png",
    "/chessPieces/White/bishop.png"
]

const currentPIeceId = ref(0);

setInterval(()=>{

    currentPIeceId.value =  (currentPIeceId.value + 1) % 6;
}, 1800)

</script>

<template>
<span class="loader">
    <img :src="allWhitePieces[currentPIeceId]" alt="">
</span>
</template>

<style scoped>
img{
    height: 2rem;
}
.loader {
    position: relative;
    display: flex;
    align-items: center;
    justify-content: center;
    width: 100%;
    max-width: 6rem;
    margin-top: 3rem;
    margin-bottom: 3rem;
  }
  .loader:before,
  .loader:after {
    content: "";
    position: absolute;
    border-radius: 50%;
    animation: pulsOut 1.8s ease-in-out infinite;
    filter: drop-shadow(0 0 1rem rgba(255, 255, 255, 0.75));
  }
  .loader:before {
    width: 100%;
    padding-bottom: 100%;
    box-shadow: inset 0 0 0 1rem #fff;
    animation-name: pulsIn;
  }
  .loader:after {
    width: calc(100% - 2rem);
    padding-bottom: calc(100% - 2rem);
    box-shadow: 0 0 0 0 #fff;
  }

  @keyframes pulsIn {
    0% {
      box-shadow: inset 0 0 0 1rem #fff;
      opacity: 1;
    }
    50%, 100% {
      box-shadow: inset 0 0 0 0 #fff;
      opacity: 0;
    }
  }

  @keyframes pulsOut {
    0%, 50% {
      box-shadow: 0 0 0 0 #fff;
      opacity: 0;
    }
    100% {
      box-shadow: 0 0 0 1rem #fff;
      opacity: 1;
    }
  }
</style>