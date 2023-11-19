#include <bits/stdc++.h> 
#include "defs.hpp"

ll compute_D(ll st_value,ll t){return st_value - t;}

ll compute_ES(ll pos,vector<ll> ST,vector<ll> positions,vector<airplane_data> airplanes){
    if(!pos) return ST[pos] - airplanes[positions[pos]].e;
    ll sp = 0;
    forn(j,0,pos) sp = max(sp,ST[j] + airplanes[positions[j]].times[positions[pos]]);
    return ST[pos] - max(airplanes[positions[pos]].e,sp);
}

void init_ST(vector<ll> &ST,vector<ll> positions,vector<airplane_data> airplanes){
    ll n = positions.size();
    ST[n - 1] = airplanes[positions[n - 1]].l;
    for(ll i = n - 2; i >= 0; i--){
        ll ps = INT_MAX;
        forn(j,i + 1,n)
            ps = min(ps,ST[j] - airplanes[positions[i]].times[positions[j]]);
        ST[i] = min(airplanes[positions[i]].l,ps);
    }

}

vector<ll> get_optimal_positions(vector<ll> positions,vector<airplane_data> airplanes){
    ll n = positions.size();
    vector<ll> ST(n),D(n),ES(n);
    init_ST(ST,positions,airplanes);
    forn(i,0,n){
        D[i] = compute_D(ST[i],airplanes[positions[i]].t);
        ES[i] = compute_ES(i,ST,positions,airplanes);
        if(D[i] > 0){
            ST[i] = ST[i] - min(D[i],ES[i]);
            D[i] = compute_D(ST[i],airplanes[positions[i]].t);
            ES[i] = compute_ES(i,ST,positions,airplanes);
        }
    }
    return ST;
}
