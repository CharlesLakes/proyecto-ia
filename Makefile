complie: main.cpp
	g++ main.cpp -o main
run: complie
	./main < input.txt