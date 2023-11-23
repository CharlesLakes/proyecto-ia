#include <bits/stdc++.h>
#include "defs.hpp"

/*
  Descripción: Función miope utilizada en la construcción Greedy para determinar la posición de una nueva aeronave.

  Parámetros:
    - values: Vector de tiempos de aterrizaje actualmente construido.
    - airplanes: Vector de estructuras airplane_data que contiene la información de las aeronaves.
    - ans: Costo acumulado actual.

  Funcionalidad:
    - Calcula dos posibles tiempos de aterrizaje para la próxima aeronave, considerando restricciones temporales.
    - Evalúa y selecciona la posición óptima para la nueva aeronave, minimizando el costo acumulado.
    - Actualiza el vector de tiempos de aterrizaje y el costo acumulado.
*/

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

/*
  Descripción: Construcción de una solución inicial utilizando el enfoque Greedy.

  Parámetros:
    - airplanes: Vector de estructuras airplane_data que contiene la información de las aeronaves.

  Salida:
    - Vector de tiempos de aterrizaje construido mediante el enfoque Greedy.

  Funcionalidad:
    - Inicia la construcción con el tiempo de aterrizaje de la primera aeronave.
    - Utiliza la función miope_function para agregar aeronaves de manera secuencial, minimizando el costo acumulado.
*/

vector<ll> gready_construction(vector<airplane_data> &airplanes){
    vector<ll> values = {airplanes[0].t};
    double cost = 0;
    forn(i,1,airplanes.size()) miope_function(values,airplanes,cost);
    return get_order(values);
}

