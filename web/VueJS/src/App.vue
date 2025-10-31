<template>
  <div class="container">
    <CustomInput />
    <button @click="show_component_method()">Show Input</button>
    <OtherOne name="Piter" />
    <OtherOne name="John" />
    <OtherOne :name="name" />
    <BlogArticle id="attribute"  :likes="12" :isPublished="true" />
  </div>
</template>

<script>
import CustomInput from "./components/CustomInput.vue";
import OtherOne from "./components/OtherOne.vue";
import BlogArticle from "./components/BlogArticle.vue";

export default {
  name: "App",
  data() {
    return {
      name: "Bruce",
    };
  },
  components: {
    CustomInput,
    OtherOne,
    BlogArticle,
  },
  methods: {
    show_component_method() {
      CustomInput.data.inputValue = "Misiaczek";
      CustomInput.methods.show_yourself();
    },
  },
};
</script>
<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
  background-color: black;
}
.container {
  background-color: brown;
}
</style>
