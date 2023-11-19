#include <bits/stdc++.h> 
#include "defs.hpp"

double eval_function(vector<ll> &values,vector<airplane_data> &airplanes,ll pos,ll penalization){
    double ans = 0;
    forn(i,pos,values.size()){
        double &g = airplanes[i].g;
        double &h = airplanes[i].h;
        ll &T = airplanes[i].t;
        ll &E = airplanes[i].e;
        ll &L = airplanes[i].l;
        // Penalización por restricciones
        ans += (double) (values[i] < E || L < values[i])*penalization;
        forn(j,0,i){
            vector<ll> &S1 = airplanes[i].times;
            vector<ll> &S2 = airplanes[j].times;
            ans += (double) (values[i] > values[j] && values[i] - values[j] < S2[i])*penalization;
            ans += (double) (values[j] > values[i] && values[j] - values[i] < S1[j])*penalization;
        }
        ans += g*max(0LL,T - values[i]) + h*max(0LL,values[i] - T);
    }
    return ans;
}

vector<airplane_data> read_data(){
    ll p; cin >> p;
    vector<airplane_data> airplanes;
    forn(i,0,p){
        airplane_data data;
        cin >> data.e >> data.t >> data.l >> data.g >> data.h;
        data.times.resize(p);
        for(ll &a: data.times) cin >> a;
        airplanes.push_back(data);
    }
    return airplanes;
}

vector<ll> get_order(vector<ll> ans){
    ll n = ans.size();
    vector<pair<ll,ll>> ord(n);
    forn(i,0,n) ord[i] = {ans[i],i};
    sort(ord.begin(),ord.end());
    vector<ll> positions(n);
    forn(i,0,n) positions[i] = ord[i].second;
    return positions;
}

vector<ll> get_revserse_order(vector<ll> positions,vector<ll> values){
    ll n = positions.size();
    vector<ll> ans(n);
    forn(i,0,n)
        ans[positions[i]] = values[i];
    return ans;
}

int main(){
    fastio;
    vector<airplane_data> airplanes = read_data();
    vector<ll> ans = gready_construction(airplanes);
    vector<ll> temp = get_order(ans); vector<ll> xd = temp;
    temp = get_optimal_positions(temp,airplanes);
    temp = get_revserse_order(xd,temp);
    cout << "Cost (real): " << eval_function(temp,airplanes,0,0) << endl;
    cout << "Cost (real): " << eval_function(ans,airplanes,0,0) << endl;
    cout << "Airplanes:\t";
    forn(i,0,ans.size()) cout << i + 1 << "\t"; cout << endl;
    cout << "Time(x_i):\t";
    for(ll a: ans) cout << a << "\t"; cout << endl;

    return 0;
}