# ASLP

## Compilación
Puedes utilizar el comando definido en el *MAKEFILE* de la siguiente forma:
```sh
make compile
```
o simplemente
```sh
make
```
En caso de que no funcione puedes usar el siguiente comando:
```sh
g++ main.cpp optimal_positions.cpp tabu_search.cpp greedy.cpp -o main
```

## Ejecución
Puedes ejecutarlo cambiando el contenido del archivo *input.txt* y lo puedes ejecutar con el siguiente comando:
```sh
make run
```
(Este comando compila y ejecuta)

En el caso que es muy complicado usar los comandos del *MAKEFILE*, puedes hacerlo de la siguiente forma (con el archivo perviamente compilado):
```sh
./main < nombre_archivo_entrada
```
(de esta forma redirigues el contenido del archivo como entrada estandar)

$\sqrt{n}$
