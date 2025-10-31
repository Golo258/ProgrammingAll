<template>
  <div>
    <h2>Fetch content</h2>
    <button @click="getLoremContent">Get Content</button>
    <div>
      <span v-if="loremContent">
        {{ loremContent }}
      </span>
    </div>
    <div>
      <h3>Count letter occurence</h3>
      <button @click="countContentLetterOccurence">Get Occurence</button>
      <ul>
        <li v-for="(letter, occurence) in letterOccurence" :key="letter">
          {{ letter }} : {{ occurence }}
        </li>
      </ul>
    </div>

    <div>
      <button @click="sortLetterObject(letterOccurence)">Sort Data</button>
      <h2>
        {{ sortedObjectData }}
      </h2>
    </div>
  </div>
</template>

<script>
export default {
  name: "App",
  data() {
    return {
      loremContent: null,
      letterOccurence: null,
      sortedObjectData: null,
    };
  },
  methods: {
    async getLoremContent() {
      try {
        const response = await fetch(
          "https://baconipsum.com/api/?type=meat-and-filler"
        );
        const content = await response.json();
        this.loremContent = content[0];
      } catch (error) {
        console.error("Error: occures ", error);
      }
    },
    countContentLetterOccurence() {
      if (this.loremContent) {
        const lettersCount = this.loremContent
          .split("")
          .reduce((acc, currentLetter) => {
            if (currentLetter.match(/[a-zA-Z]/)) {
              currentLetter = currentLetter.toLowerCase();
              if (acc[currentLetter]) {
                acc[currentLetter] += 1;
              } else {
                acc[currentLetter] = 1;
              }
            }
            return acc;
          }, {});
        console.log(lettersCount);
        this.letterOccurence = lettersCount;
      } else {
        console.log("empty");
      }
    },
    sortLetterObject(letterObject) {
      const sortedData = Object.entries(letterObject)
        .sort((a, b) => a[1] - b[1]) // Sortowanie po wartościach
        .reduce((acc, [key, value]) => {
          acc[key] = value;
          return acc;
        }, {});
      console.log(sortedData);
      this.sortedObjectData = sortedData;
    },
  },
  computed: {},
};
</script>

<style>

ul {
  list-style-type: none;
}
</style>
