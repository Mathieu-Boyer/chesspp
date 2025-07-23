<script setup>
import Button from "primevue/button"
import { Form } from '@primevue/forms';
import { InputText } from "primevue";

</script>

<template>

    <div class="container">
        <Form class="form">
            <InputText name="email" type="email" placeholder="email" />
            <InputText name="password" type="password" placeholder="password"/>
            <Button label="Sign in"/>
        </Form>
    </div>

</template>

<style scoped>
    .container{
        display: flex;
        align-items: center;
        justify-content: center;
        flex-direction: column;
        padding: 3rem;
        width: fit-content;
        background-color: #312e2b;
        border-radius: .5rem;
    }
    .form{
        display: flex;
        flex-direction: column;
        gap: 0.5rem;
        width: 20rem;
    }

    input {
        border: #6a6a6a solid 1px;
    }
    
    button {
        margin-top: 1rem;
    }
</style>