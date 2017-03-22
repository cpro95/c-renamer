namer: main.cpp utils.cpp
	g++ -o namer main.cpp utils.cpp curses_util.cpp -I. -lncurses

clean:
	rm -rf *.exe

