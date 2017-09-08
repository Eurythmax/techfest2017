<template>
  <div id="app">

      <el-tabs v-model="activeName" @tab-click="handleClick">
        <el-tab-pane label="All Transactions" name="first"></el-tab-pane>
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

  components: {
  //  LiveAdminTable
  },

  methods: {

    handleClick(tab, event) {
      console.log('switching to another tab');
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
