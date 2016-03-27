all:
	g++ *.cpp -std=c++0x -o village
	./village > results.txt
	tail -n 100 results.txt
