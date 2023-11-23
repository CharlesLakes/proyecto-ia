#include <bits/stdc++.h>
#include "defs.hpp"


/*
  Descripción: Implementación de una lista Tabú para el algoritmo de búsqueda Tabú.

  Estructura de Datos:
    - N: Tamaño máximo de la lista Tabú.
    - m_values: Mapa que almacena el número de veces que una solución específica ha estado en la lista.
    - q_values: Cola que mantiene el orden de las soluciones en la lista Tabú.

  Funciones:
    - TabuList(ll _N): Constructor que recibe el tamaño máximo de la lista Tabú.
    - bool find(vector<ll> &values): Verifica si una solución está en la lista Tabú.
    - void pop(): Elimina la solución más antigua de la lista Tabú.
    - void push(vector<ll> &values): Agrega una nueva solución a la lista Tabú, gestionando su frecuencia.
*/struct TabuList{
    ll N;
    map<vector<ll>,ll> m_values;
    queue<vector<ll>> q_values;
    TabuList(ll _N){N = _N;};
    bool find(vector<ll> &values){return m_values[values];};
    void pop(){
        if(m_values.empty()) return;
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

/*
  Descripción: Genera todas las permutaciones el swap de posiciónes de dos elementos consecutivos en un vector.

  Parámetros:
    - pos: Vector de posiciones.

  Retorno: Vector de vectores representando todas las permutaciones de posiciones.

  Detalles adicionales:
    - Para cada posición i, intercambia los elementos en las posiciones i e i+1 para crear una permutación.
    - Genera todas las permutaciones posibles y las devuelve en un vector de vectores.
*/

vector<vector<ll>> get_swaps(vector<ll> &pos){
    ll n = pos.size();
    vector<vector<ll>> ans(n,pos);
    forn(i,0,n) swap(ans[i][i],ans[i][(i + 1) % n]);
    return ans;
}

/*
  Descripción: Implementación del algoritmo de Tabu Search para optimización. 
               Encuentra la mejor solución a partir de una solución inicial Sc y una lista de aviones.

  Parámetros:
    - Sc: Solución inicial.
    - v_best: Mejor valor de la función de evaluación.
    - airlpanes: Vector de datos de aviones.

  Retorno: Vector representando la mejor solución encontrada.

  Detalles adicionales:
    - La función utiliza una lista tabú para gestionar movimientos prohibidos y evitar ciclos.
    - Se realizan iteraciones limitadas (100) para encontrar la mejor solución.
    - La función evalúa múltiples intercambios de posiciones y selecciona el mejor movimiento no tabú.
    - Se utiliza una función de evaluación para determinar la calidad de las soluciones.
    - Se muestra información detallada sobre el progreso, incluyendo el número de iteración, el tamaño de la lista tabú y los valores actuales de Sc y Sbest.
*/
vector<ll> TabuSearch(vector<ll> Sc,ll v_best,vector<airplane_data> airlpanes){
    ll iteration = 100;
    TabuList tl(30);
    vector<ll> Sbest = Sc;
    ll cnt = 0;
    while(iteration --> 0 ){
        auto swaps = get_swaps(Sc);
        ll best = INT_MAX,pos = -1;
        forn(i,0,swaps.size()){
            auto &sw = swaps[i];
            if(!tl.find(sw)){
                vector<ll> values = get_optimal_positions(sw,airlpanes);
                values = get_revserse_order(sw,values);
                ll v = eval_function(values,airlpanes);
                if(best > v){
                    best = v;
                    pos = i;
                }
            }
        }
        if(pos == -1) break;
        Sc = swaps[pos];
        tl.push(swaps[pos]);
        //cout << v_best << " " << best << endl;
        if(v_best > best) v_best = best,Sbest = swaps[pos];
        else tl.pop();
        cout << "\tN° iteration: " << ++cnt << "\tTabu List Size: " << tl.q_values.size() << endl;
        cout << "\tSc: " << best << "\tSbest: " << v_best << endl << endl;
    }

    return Sbest;

}


