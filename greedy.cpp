#include <bits/stdc++.h>
#include "defs.hpp"

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
    return values;
}

