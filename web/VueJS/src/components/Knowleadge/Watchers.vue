<template>
  <div>
    <h2>Current Volume : {{ volume }}</h2>
    <div>
      <button @click="volume += 2">Increase</button>
      <button @click="volume -= 2">Decrease</button>
    </div>

    <div style="margin-top: 20px">
      <label for="move">Movie: </label>
      <input id="movie" type="text" v-model="movie" />
    </div>

    <div style="margin-top: 20px">
      <label> Series Infos: </label>
      <input type="text" v-model="seriesInfo.title" />
      <input type="text" v-model="seriesInfo.actors" />
    </div>
  </div>
</template>

<script>
export default {
  name: "App",
  data() {
    return {
      volume: 0,
      movie: "SAO",
      seriesInfo: {
        title: "",
        actors: "",
      },
    };
  },
  methods: {},
  computed: {},
  watch: {
    volume(new_volume, old_value) {
      if (new_volume > old_value && new_volume === 20) {
        alert("Stop increasing. It's dangerous");
      }
    },
    movie: {
      handler(new_value) {
        console.log(`Checking movie: ${new_value}`);
      },
      immediate: true,
    },
    seriesInfo: {
      handler(new_value) {
        console.log(
          `Checking series infos: ${new_value.title} and actors: ${new_value.actors}`
        );
      },
      deep: true,
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
}
</style>
