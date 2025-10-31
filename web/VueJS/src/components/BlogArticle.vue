<template>
    <div>
        <h2>Article Component</h2>
        <h2>{{ title }}</h2>
        <h2>{{ likes }}</h2>
        <h2 v-bind="$attrs">Is Published: {{ isPublished ? "Yes" : "No"}}</h2>
    </div>
</template>

<script>
    export default {
        name : "BlogArticle",
        props: {
            title : {
                type : String,
                required : true,
                default: "eso es muy simple"
            },
            likes : Number ,
            isPublished : Boolean,

        },
        inheritAttrs: false,
        
    }
</script>