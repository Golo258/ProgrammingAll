<template>
    <div>
      <div v-for="name in namesArray" :key="name">
        <h2 v-if="name.length % 2 === 0">
          {{ name }}
          <input placeholder="Last name" />
          <hr/>
        </h2>
      </div>
      <button @click="shuffle">Shuffle</button>
    </div>
</template>

<script>
import _ from "lodash";

export default {
  name: "App",
  data() {
    return {
      namesArray: ["Jakes", "Steven", "Mark", "Barry"],
    };
  },
  methods: {
    shuffle() {
      console.log(this.namesArray);
      this.namesArray = _.shuffle(this.namesArray);
    }
  }
};
</script>
