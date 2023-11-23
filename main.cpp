#include <bits/stdc++.h> 
#include "defs.hpp"

/*
  Descripción: Función para evaluar la función objetivo del problema de programación de aterrizaje de aeronaves.

  Parámetros:
    - values: Vector de tiempos de aterrizaje para cada aeronave.
    - airplanes: Vector de estructuras airplane_data que contiene la información de las aeronaves.
    - pos: Posición desde la cual se evalúa la función objetivo.
    - penalization: Valor de penalización para las restricciones incumplidas.

  Salida:
    - Valor de la función objetivo evaluada.

  Funcionalidad:
    - Calcula el valor de la función objetivo para un conjunto dado de tiempos de aterrizaje.
    - Considera penalizaciones por incumplimiento de restricciones y restricciones de tiempo entre aeronaves.
    - La evaluación se realiza a partir de la posición especificada (pos) hasta el final del vector values.

  Observación:
    - La función asume que los valores proporcionados cumplen con un formato y rango específicos.
*/
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
        ans += g*max((ll)0,T - values[i]) + h*max((ll)0,values[i] - T);
    }
    return ans;
}

/*
  Descripción: Función para leer datos relacionados con la programación de aterrizajes de aeronaves.

  Parámetros:
    - Ninguno.

  Salida:
    - Vector de estructuras airplane_data que representan la información de las aeronaves.
*/
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
    //fastio;
    clock_t begin = clock();
    vector<airplane_data> airplanes = read_data();
    vector<ll> positions = gready_construction(airplanes); 
    vector<ll> values = get_optimal_positions(positions,airplanes);
    vector<ll> values_order = get_revserse_order(positions,values);
    cout << "Greedy: " << endl;
    ll cost = eval_function(values_order,airplanes);
    cout << "\tCost: " << cost << endl;
    cout << "\tPosiciones: " << endl;
    forn(i,0,values_order.size())
        cout << "\t\t" << i + 1 << ": " << values_order[i] << endl;

    positions = TabuSearch(positions,cost,airplanes);
    values = get_optimal_positions(positions,airplanes);
    values_order = get_revserse_order(positions,values);
    cout << "TabuSearch: " << endl;
    cost = eval_function(values_order,airplanes);
    cout << "\tCost: " << cost << endl;
    cout << "\tPosiciones: " << endl;
    forn(i,0,values_order.size())
        cout << "\t\t" << i + 1 << ": " << values_order[i] << endl;
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "Time: " << time_spent << endl;
    return 0;
}