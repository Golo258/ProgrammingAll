<template>
  <div>
    <div v-if="words.length > 0">
      <h2 v-for="word in words" :key="word">
        {{ word }}
      </h2>
    </div>
    <button v-on:mouseover="add_word()">Add Word</button>
    <button v-on:mouseout="remove_word()">Remove Name</button>
    <div>
      <button @click="change_word">Change Name</button>
      <button @click="add_bunch_of_words(3, $event)">Add some words</button>
    </div>
  </div>
</template>

<script>
export default {
  name: "App",
  data() {
    return {
      words: [],
    };
  },
  methods: {
    add_word() {
      const result = Math.random().toString(36).substring(2, 10);
      console.log(result);
      this.words.push(result);
    },
    remove_word() {
      const item_index = Math.floor(Math.random() * this.words.length);
      console.log(item_index);
      this.words.splice(item_index, 1);
    },
    change_word(event) {
      if (this.words.length > 0) this.words[0] = this.words[0].slice(0, 3);
      console.log("Event", event);
      
    },
    add_bunch_of_words(words_count, event) {
      const len = this.words.length;
      for (let index = len; index < len + words_count; index += 1) {
        this.words.push("additional" + index);
      }
      console.log(event.type);
    },
  },
};
</script>
