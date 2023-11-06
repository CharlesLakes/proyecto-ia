#include <bits/stdc++.h> 
#include "defs.hpp"

using namespace std;

struct airplane_data{
    ll e,t,l;
    double g,h;
    vector<ll> times;
};

double eval_function(vector<ll> &values,vector<airplane_data> &airplanes,ll pos = 0,ll penalization = 1000){
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

void miope_function(vector<ll> &values,vector<airplane_data> &airplanes,double &ans){
    ll pos = values.size();
    ll c1,c2; c1 = c2 = airplanes[pos].t;
    forn(i,0,values.size()) c1 = max(c1,values[i] + airplanes[i].times[pos]);
    forn(i,0,values.size()) c2 = min(c2,values[i] - airplanes[pos].times[i]);
    
    // Primera posibilidad
    values.push_back(c1);
    double ans1 = ans + eval_function(values,airplanes,pos);
    values.pop_back();

    // Segunda posibilidad
    values.push_back(c2);
    double ans2 = ans + eval_function(values,airplanes,pos);
    values.pop_back();

    if(ans1 < ans2) values.push_back(c1);
    else values.push_back(c2);
    ans = min(ans1,ans2);
}

vector<ll> gready_construction(vector<airplane_data> &airplanes){
    vector<ll> values = {airplanes[0].t};
    double cost = 0;
    forn(i,1,airplanes.size()) miope_function(values,airplanes,cost);
    cout << "Cost (eval function): " << cost << endl;
    return values;
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

int main(){
    fastio;
    vector<airplane_data> airplanes = read_data();
    vector<ll> ans = gready_construction(airplanes);
    cout << "Cost (real): " << eval_function(ans,airplanes,0,0) << endl;
    cout << "Airplanes:\t";
    forn(i,0,ans.size()) cout << i + 1 << "\t"; cout << endl;
    cout << "Time(x_i):\t";
    for(ll a: ans) cout << a << "\t"; cout << endl;

    return 0;
}