renamer: renamer.cpp renamer_util.cpp
	g++ -o renamer renamer.cpp renamer_util.cpp -I. -lncurses

clean:
	rm -rf *.exe

