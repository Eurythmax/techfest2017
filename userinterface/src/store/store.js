import Vue from 'vue'
import Vuex from 'vuex'

import mentorData from './data.json'

console.log(mentorData);

var transactionList = new Array();

Vue.use(Vuex)

export default new Vuex.Store({
    state: {
        connect: false,
        transactions: transactionList
    },
    mutations:{

        ADD_TRANSACTION: (state, transaction ) => {
            state.transactions.push(transaction);
        }
    },
    actions: {
        addLiveTransaction(context, t){
          context.commit('ADD_TRANSACTION',t)
        }

    }
})
