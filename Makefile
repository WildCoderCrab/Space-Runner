all:
	g++ -c src/*.cpp -std=c++14 -m64 -Wall
	g++ *.o -o bin/SpaceRunner -lraylib -lGL -ldl -lrt -lpthread
