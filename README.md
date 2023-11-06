# ASLP

## Compilación
Puedes utilizar el comando definido en el *MAKEFILE* de la siguiente forma:
```sh
make compile
```
En caso de que no funcione puedes usar el siguiente comando:
```sh
g++ main.cpp -o main
```

## Ejecución
Puedes ejecutarlo cambiando el contenido del archivo *input.txt* y lo puedes ejecutar con el siguiente comando:
```sh
make run
```
(Este comando compila y ejecuta)

En el caso que es muy complicado usar los comandos del *MAKEFILE*, puedes hacerlo de la siguiente forma:
```sh
./main < nombre_archivo_entrada
```
(de esta forma redirigues el contenido del archivo como entrada estandar)
