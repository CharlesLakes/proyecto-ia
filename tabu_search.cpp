#include <bits/stdc++.h>
#include "defs.hpp"

struct TabuList{
    ll N;
    map<vector<ll>,ll> m_values;
    queue<vector<ll>> q_values;
    TabuList(ll _N){N = _N;};
    bool find(vector<ll> &values){return m_values[values];};
    void pop(){
        auto temp = q_values.front(); q_values.pop();
        m_values[temp]--;
        if(!m_values[temp]) m_values.erase(temp);
    };
    void push(vector<ll> &values){
        q_values.push(values);
        m_values[values]++;
        while(q_values.size() > N) pop();
    }
};

vector<vector<ll>> get_swaps(vector<ll> &pos){
    ll n = pos.size();
    vector<vector<ll>> ans(n,pos);
    forn(i,0,n) swap(ans[i],ans[(i + 1) % n]);
    return ans;
}

vector<ll> TabuSearch(vector<ll> Sc,ll v_best,vector<airplane_data> airlpanes){
    ll iteration = 100;
    TabuList tl(30);
    vector<ll> Sbest = Sc;
    while(iteration--){
        auto swaps = get_swaps(Sc);
        ll best = INT_MAX,pos = -1;
        forn(i,0,swaps.size()){
            auto &sw = swaps[i];
            if(!tl.find(sw)){
                vector<ll> values = get_optimal_positions(sw,airlpanes);
                values = get_revserse_order(sw,values);
                ll v = eval_function(values,airlpanes);
                if(best > v) v = best, pos = i;
            }
        }
        if(pos == -1) break;
        Sc = swaps[pos];
        tl.push(swaps[pos]);
        if(v_best > best) v_best = best,Sbest = swaps[pos];
    }

    return Sbest;

}


