main.o:
	g++ main.cpp -c 
optimal_positions.o:
	g++ optimal_positions.cpp -c
greedy.o:
	g++ greedy.cpp -c
tabu_search.o:
	g++ tabu_search.cpp -c
complie: main.o optimal_positions.o tabu_search.o greedy.o
	g++ main.o optimal_positions.o tabu_search.o greedy.o -o main
run: complie
	./main < input.txt