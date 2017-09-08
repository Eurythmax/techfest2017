import Vue from 'vue'
import ElementUI from 'element-ui'
import 'element-ui/lib/theme-default/index.css'
import App from './components/App.vue'
import store from './store/store'
import VueRouter from 'vue-router'
import router from './router/router.js'
import VueSocketio from 'vue-socket.io';

Vue.use(VueSocketio, 'http://localhost:3001');
Vue.use(VueRouter)
Vue.use(ElementUI)

new Vue({
  router,
  store,
  el: '#app',
  render: h => h(App)
})
