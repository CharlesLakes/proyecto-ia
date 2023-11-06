---
marp: true
math: mathjax
class: invert
---

# Estado de Avance ASLP (Greedy + TS)
Carlos Lagos Cortés

---
## Estructura para almacenar los datos de cada avión
```c++
struct airplane_data{
    ll e,t,l;
    double g,h;
    vector<ll> times;
};
```
---

## Lectura de las instancias
```c++
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
```

---

## Representación
La solución se representó utilizando un vector de números enteros, donde cada posición corresponde al número de avión y su contenido indica el tiempo de aterrizaje.
Es decir, se vería de la siguiente manera:
```c++
vector<long long> values;
// ejemplo: values = {10,2,5}
// Esto indica que el primer avión tendra asignado el tiempo 10 y de esta forma con los demas aviones
```

---

## Restricciónes 

Enfrentamos las restricciones de la siguiente manera: si el tiempo $x_i$ no se encuentra en el intervalo adecuado o no se respeta la separación requerida, se aplica una penalización en la función de evaluación. Además, al construir la solución greedy, garantizamos que cumple con la restricción de separación. Esta aproximación evita bloqueos o atascos durante la iteración del algoritmo greedy o reparadores.

---

## Solución Inicial

La solución inicial se genera mediante el algoritmo greedy, un algoritmo constructivo que utiliza la función de evaluación y una función miope.
**Función de Evaluación:**
- Calcula el costo de la solución actual.
- Aplica penalizaciones por restricciones.

**Función Miope:**
- Añade el siguiente avión de la lista, asignándole el tiempo más temprano o más tardío en relación con los aviones actuales, eligiendo la opción que minimice el costo.
- Asegura que el avión cumpla con las condiciones de separación con los aviones ya colocados en la solución.

---

## Función de evaluación

Puedes observar esto en el siguiente código, donde se define la función de evaluación que calcula el costo actual e incorpora penalizaciones por restricciones.
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

## Función miope

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

## Greedy
```c++
vector<ll> gready_construction(vector<airplane_data> &airplanes){
    vector<ll> values = {airplanes[0].t};
    double cost = 0;
    forn(i,1,airplanes.size()) miope_function(values,airplanes,cost);
    return values;
}
```
---

## Algoritmo (Tabu Search)

* **Representación:** Utiliza un vector o lista de enteros que asigna el tiempo $x_i$ a cada avión $i$.

* **Función de evaluación:** Calcula el costo de la solución y, si incumple una restricción, la penaliza para evitar su elección.

* **Lista tabú:** Inicialmente vacía, se representa mediante una cola y un set para una búsqueda eficiente $O(log(n))$ y para eliminar rápidamente el último elemento cuando la lista está llena $O(log(n))$.

---

## Movimiento

Para generar un movimiento para cada tiempo $x_i$ asociado a los aviones, se permite aumentar o disminuir en una unidad el tiempo de aterrizaje de cualquiera de los aviones. Se opta por esta opción en lugar de un cambio en un factor $\alpha$, ya que el último podría pasar por alto soluciones óptimas. El propósito es modificar las características de la solución para intensificar o diversificar la búsqueda.

---

## Conclusión

En esta etapa, se ha completado la implementación de la solución greedy, que se encarga de construir la solución inicial. Aunque se ha planteado la implementación de la reconstrucción con Tabu Search, aún no se ha llevado a cabo. Es crucial considerar que el estudio y posible mejora del movimiento es un paso fundamental para buscar soluciones de manera más eficiente y efectiva. En el próximo ciclo de desarrollo, se espera explorar a fondo esta área y avanzar en la implementación de Tabu Search para obtener resultados más óptimos y satisfactorios.

---

# Bibliografía

<ul style="font-size:23px;">
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


