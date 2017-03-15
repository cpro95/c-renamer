namer: main.cpp utils.cpp
	g++ -o namer main.cpp utils.cpp -I. -lncurses

clean:
	rm -rf *.exe

