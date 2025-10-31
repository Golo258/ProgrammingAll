<template>
  <div>Kolano SIemano {{ name }}</div>
  <div v-text="channel"></div>
  <div v-html="header"></div>
  <div v-html="alert"></div>
  <h2 v-bind:id="headingID">Heading</h2>
  <button :disabled="isPromoted">Bind</button>
  <div :class="isPromoted && 'promoted'">Simple Text</div>
  <div :class="isPromoted ? 'promoted' : 'underlined'">Simple Text</div>
  <div
    v-bind:class="[
      isPromoted && 'promoted',
      isUnderlined ? 'underlined' : 'empty',
    ]"
  >
    Last Text
  </div>

  <div v-bind:class="{
      promoted: isPromoted,
      underlined: isUnderlined,
    }"> The Lastest Text  </div>

  <h2 v-bind:style="{
    color: lineColor,
    textDecoration: 'underline'
  }"> Inline </h2> 
   <h1  v-bind:style="headerStyleObject">
      Wystylizowany nagłówek
   </h1>
</template>

<script>
export default {
  name: "App",
  data() {
    return {
      name: "Grzesiuniunia",
      channel: "Simple",
      header: "<h1> Biggest One </h1> ",
      alert: ` <a href="#" onclick="alert('Siemano kolano')">Win a price</a>`,
      headingID: "heading",
      isPromoted: true,
      isUnderlined: true,
      status: "success",
      lineColor: "orange",
      headerStyleObject : {
        color : "green",
        fontSize: '50px',
        padding: '20px'
      },

    };
  },
};
</script>

<style>
  .underlined {
    text-decoration: underline;
  }
  .empty {
    text-decoration: none;
    color: green;
  }
  .promoted {
    font-style: italic;
  }
}
</style>
