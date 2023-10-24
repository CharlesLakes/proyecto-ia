#include <bits/stdc++.h> 
#include "defs.hpp"

using namespace std;

struct airplane_data{
    ll e,t,l;
    double g,h;
    vector<ll> times;
};

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
    


    return 0;
}