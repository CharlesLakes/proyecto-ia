---
marp: true
math: mathjax
theme: academic
---

<!-- _class: lead -->

# ALSP (Greedy + TS)

Nombre: Carlos Lagos Cortés
Rol: 202073571-9

---

<!-- _class: lead -->

## Greedy: Construcción de una solución inicial
* Representación
* Función miope
* Función de evaluación
---

<!-- _header: Greedy: Construcción de una solución inicial -->

### Representación

Se emplea un vector donde la posición $i$-ésima del arreglo almacena el tiempo $x_i$ asignado al avión $i$.
```c++
#define long long ll;
// ...
vector<ll> values; // Vector que guarda los valores de x_i
```
---

<!-- _header: Greedy: Construcción de una solución inicial -->

### Función de evaluación
- Calcula el costo de la solución actual.
- Aplica penalizaciones por restricciones.

---

<!-- _header: Greedy: Construcción de una solución inicial -->

```c++
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
```

---

<!-- _header: Greedy: Construcción de una solución inicial -->
### Función miope
- Añade el siguiente avión de la lista, asignándole el tiempo más temprano o más tardío en relación con los aviones actuales, eligiendo la opción que minimice el costo.
- Asegura que el avión cumpla con las condiciones de separación con los aviones ya colocados en la solución.

---
<!-- _header: Greedy: Construcción de una solución inicial -->

```c++
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
```
---

<!-- _class: lead -->
## Tabu Search: Mejorar solución
* Representación
* Movimiento
* Posiciones optimas $O(n^3)$
* Función de evaluación
* Lista tabu
* Implemementción general

---

<!-- _header: Tabu Search: Mejorar solución -->

### Representación

<style scoped>
    p{
        font-size:28px;
    }
</style>

Para la representación, se utiliza un vector $A[0...n - 1]$ que guarda la secuencia de orden de aterrizaje. Es decir, el avión $A[i]$ aterriza en la posición $i$-ésima con respecto al conjunto de aviones.

```c++
#define long long ll;
// ...
vector<ll> A; // Contiene la secuancia A 
```

Para transformar la representación definida en el algoritmo greedy y adaptarla a la utilizada en Tabu Search, simplemente se ordenaron las posiciones asignadas $x_i$ y se organizaron en función de este valor para obtener la secuencia de aterrizaje.

---

<!-- _header: Tabu Search: Mejorar solución -->

### Movimiento

El movimiento definido sobre la secuencia $A[0...n - 1]$ de longitud $n$ consiste en intercambiar el elemento actual con el siguiente, teniendo en cuenta que esta operación se puede realizar de forma cíclica. Más formalmente, se puede intercambiar $A_i$ y $A_{(i +  1)\% n}$ para cualquier $i$.

```c++
vector<vector<ll>> get_swaps(vector<ll> &pos){
    ll n = pos.size();
    vector<vector<ll>> ans(n,pos);
    forn(i,0,n) swap(ans[i][i],ans[i][(i + 1) % n]);
    return ans;
}
```

---

<!-- _header: Tabu Search: Mejorar solución -->

### Posiciones optimas $O(n^3)$

<style scoped>
    p,li{
        font-size:28px;
    }
</style>

Se empleará un algoritmo descrito en el artículo de **Abhinav Awasthi**, que toma como entrada una secuencia específica de aterrizaje. El procedimiento consta de los siguientes pasos:

1. Inicialmente, asignamos a todos los aviones el tiempo de aterrizaje más tardío posible, asegurándonos de que estén dentro de su intervalo de tiempo. Esta asignación comienza desde el último avión hasta el primero, respetando las separaciones necesarias.

2. Iniciamos la asignación de posiciones desde el inicio de la secuencia. En cada iteración, calculamos la diferencia entre la posición actual y el punto óptimo $D$, y también determinamos la cantidad máxima que podemos adelantar el vuelo $ES$ según la asignación inicial. Finalmente estamos a la asignación inicial el mínimo entre $ES$ y $D$.

---

<!-- _header: Tabu Search: Mejorar solución -->

```c++
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
```
---

<!-- _header: Tabu Search: Mejorar solución -->
### Función de evaluación
Se empleó el mismo algoritmo que en el apartado Greedy, pero su implementación requiere la conversión de la representación $A$ a la representación $X$. 
El proceso se lleva a cabo de la siguiente manera:

- Se calcula el costo de la solución actual.

- Se aplican penalizaciones por restricciones.

---
<!-- _header: Tabu Search: Mejorar solución -->
<style scoped>
    p,li{
        font-size:28px;
    }
</style>

### Lista Tabu

Para su implementación, se utilizó un "map" para verificar rápidamente si un elemento pertenece en $O(\log n)$ (si el elemento almacenado tiene una longitud variable, se debe multiplicar la longitud en la complejidad). Además, se empleó una "queue" para determinar qué elemento eliminar cuando la lista alcance su límite.

Se guardó la representación completa de la solución; sin embargo, verificar la pertenencia es $O(\text{SIZE} \cdot \log n)$. Esta eficiencia se puede mejorar mediante una técnica llamada Rolling Hashing. En resumen, consiste en convertir el vector en un número y utilizar ese número como identificador en la lista tabú. En caso de colisión, se puede aplicar doble Rolling Hashing o K-Rolling Hashing.

El límite definido, basado en una proporción entre resultados y eficiencia, es de 30 elementos.


---

<!-- _header: Tabu Search: Mejorar solución -->

```c++
struct TabuList{
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
```
---

<!-- _header: Tabu Search: Mejorar solución -->

<style scoped>
    h3{
        font-size:25px;
    }
</style>

### Implementación general
```c++
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
```
---

<!-- _class: lead -->
## Resultados y Observaciones

---

<!-- _header: Resultados -->

### Resultados

| N° | Tamaño de entrada | Costo | Tiempo (seg) | Archivo |
|---|---|---|---| --- |
| 1 | 10 | 1150 | 0.03125 | airland1.txt |
| 2 | 15 | 1720 |  0.125 | airland2.txt |
| 3 | 20 | 1610 | 0.265620 | airland3.txt |
| 4 | 20 | 27560 | 0.265625 | airland4.txt |
| 5 | 44 | 1648 | 2.375 | airland7.txt |
| 6 | 150 | 34165 |  96.0781 | airland10.txt |

---

<!-- _header: Resultados -->

### Observaciones

Se puede observar que en todos los casos se calculó una respuesta aceptable, pero en los casos 4 y 6 se observa un costo muy elevado, probablemente debido a que la solución encontrada no cumple con las restricciones y, por ende, es penalizada. Además, se observa que hay una relación entre el tamaño y el tiempo de ejecución.

---

## Conclusión

<style scoped>
    p{
        font-size:26px;
    }
</style>

En resumen, la combinación de estrategias Greedy y Tabu Search ha demostrado ser eficaz en la optimización de horarios de aterrizaje de aeronaves en el Aircraft Landing Scheduling Problem (ALSP). Los resultados indican una relación directamente proporcional entre el tamaño del problema y el tiempo de ejecución del algoritmo, subrayando la importancia de considerar la eficiencia computacional en instancias más grandes.

Aunque se observaron costos elevados en los casos 4 y 6, posiblemente debido a incumplimientos de restricciones, la investigación ofrece perspectivas prometedoras para futuras adaptaciones de estrategias más eficientes en problemas más complejos de programación de aterrizajes de aeronaves.

Se destaca la mejora potencial en la implementación de la lista tabú mediante la propuesta de utilizar Rolling Hashing.

---

## Bibliografía

<ul style="font-size:20px;">
    <li>Abhinav Awasthi, Oliver Kramer, and Jorn Lassig. Aircraft landing problem: An efficient
algorithm for a given landing sequence. In 2013 IEEE 16th International Conference on
Computational Science and Engineering, 2013.</li>
    <li>J. E. Beasley, M. Krishnamoorthy, Y. M. Sharaiha, and D. Abramson. Scheduling aircraft
landings a the static case. 1990.</li>
    <li>J. E. Beasley, M. Krishnamoorthy, Y. M. Sharaiha, and D. Abramson. Displacement problem
and dynamically scheduling aircraft landings. Journal of the Operational Research Society,
55(1):54–64, 2004.</li>
    <li> Ghizlane Bencheikh, Jaouad Boukachour, Fatima Khoukhi, and Ahmed Alaoui. Hybrid
method for aircraft landing scheduling based on a job shop formulation. International Journal
of Computer Science and Network Security, 9:78 – 88, 08 2009.</li>
    <li> Alberto Colorni, Marco Dorigo, Vittorio Maniezzo, and Marco Trubian. Ant system for
job-shop scheduling. STATISTICS AND COMPUTER SCIENCE, 34, 01 1994.</li>
    <li> Maurice Pollack. Some aspects of the aircraft scheduling problem. Transportation Research,
8(3):233–243, 1974.</li>
    <li>Amir Salehipour. An algorithm for single–and multiple-runway aircraft landing problem. 5
2018</li>
</ul>



