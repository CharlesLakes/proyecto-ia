complie: main.o optimal_positions.o tabu_search.o greedy.o
	g++ main.o optimal_positions.o tabu_search.o greedy.o -o main
run: complie
	./main < input.txt
main.o: main.cpp
	g++ main.cpp -c 
optimal_positions.o: optimal_positions.cpp
	g++ optimal_positions.cpp -c
greedy.o: greedy.cpp
	g++ greedy.cpp -c
tabu_search.o: tabu_search.cpp
	g++ tabu_search.cpp -c
clean:
	rm *.o ./main