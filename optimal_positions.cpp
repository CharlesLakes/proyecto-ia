#include <bits/stdc++.h> 
#include "defs.hpp"

/*
  Descripción: Función que calcula el tiempo de demora (D) para una posición de aterrizaje dada y un tiempo objetivo.

  Parámetros:
    - st_value: Valor del tiempo asignado para la aeronave en la secuencia.
    - t: Tiempo objetivo.

  Retorna:
    - Valor del tiempo de demora (D).
*/
ll compute_D(ll st_value,ll t){return st_value - t;}

/*
  Descripción: Función que calcula el tiempo de salida anticipada (ES) para una posición de aterrizaje dada.

  Parámetros:
    - pos: Posición actual en la secuencia de aterrizaje.
    - ST: Vector de tiempos asignados para las aeronaves en la secuencia actual.
    - positions: Vector que representa la secuencia actual de aterrizaje.
    - airplanes: Vector de estructuras airplane_data que contiene la información de las aeronaves.

  Retorna:
    - Valor del tiempo de salida anticipada (ES).
*/

ll compute_ES(ll pos,vector<ll> ST,vector<ll> positions,vector<airplane_data> airplanes){
    if(!pos) return ST[pos] - airplanes[positions[pos]].e;
    ll sp = 0;
    forn(j,0,pos) sp = max(sp,ST[j] + airplanes[positions[j]].times[positions[pos]]);
    return ST[pos] - max(airplanes[positions[pos]].e,sp);
}


/*
  Descripción: Función que inicializa los tiempos asignados (ST) para una secuencia dada de aeronaves.

  Parámetros:
    - ST: Vector de tiempos asignados a inicializar.
    - positions: Vector que representa la secuencia actual de aterrizaje.
    - airplanes: Vector de estructuras airplane_data que contiene la información de las aeronaves.
*/
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
/*
  Descripción: Función que calcula las posiciones óptimas de aterrizaje para una secuencia dada de aeronaves.

  Parámetros:
    - positions: Vector que representa la secuencia actual de aterrizaje.
    - airplanes: Vector de estructuras airplane_data que contiene la información de las aeronaves.
*/
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
