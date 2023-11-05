---
marp: true
math: mathjax
class: invert
---

# Estado de Avace ALSP (Greedy + TS)
Carlos Lagos

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
```

---

