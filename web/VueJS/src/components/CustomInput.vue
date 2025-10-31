<template>
  <div>
    <input type="text" v-model="inputValue" placeholder="Type something" />
    <p>Enter some value: {{ inputValue }}</p>
  </div>
</template>

<script>
export default {
  name: "CustomInput",
  data() {
    return {
      inputValue: "",
    };
  },
  methods: {
    show_yourself() {
      console.log("Siemano kolano ");
    },
  },
};
</script>

<style scoped></style>
