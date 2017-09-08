<template>
  <div id="app">

      <el-tabs v-model="activeName" @tab-click="handleClick">
        <el-tab-pane label="User" name="first"></el-tab-pane>
        <el-tab-pane label="Config" name="second"></el-tab-pane>
        <el-tab-pane label="Role" name="third"></el-tab-pane>
      </el-tabs>


    <router-view></router-view>

  </div>
</template>

<script>
import Mentors from './LiveAdminTable.vue';
import store from '../store/store.js';
import router from '../router/router.js';

import VueSocketio from 'vue-socket.io';

export default {
  data () {
    return {
      msg: 'Use Vue 2.0 Today!'
    }
  },
  components: {
    Mentors
  },

  methods: {

    handleClick(tab, event) {
      console.log("boo");
      router.push({ path: 'admin' })

    }
  },

  sockets:{
    connect: function(){
      console.log('socket connected')
    },
    transactionCreated: function(m){
      console.log(m);
      store.dispatch('addLiveTransaction',m)
    }

  }


}
</script>

<style>
body {
  font-family: Helvetica, sans-serif;
}
</style>
