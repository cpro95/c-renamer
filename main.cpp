//============================================================================
// Name        : avi_smi_namer.cpp
// Author      : cpro95
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : AVI, SMI Namer by cpro95
//============================================================================

#include <iostream>
#include <ncurses.h>
#include "utils.h"

// global variables
std::vector<std::string> vMovieFiles;
std::vector<std::string> vSmiFiles;

void init_scr();

int main()
{
	// initialize varables
	int ch;
	
	// init ncurses window
	init_scr();

	// print welcome ment
	mvprintw(0,0,"Hello renamer util - by cpro95@gmail.com");
	refresh();
	mvprintw(1,0, "Press F10 to exit");
	refresh();

/*
	loadFiles(".");
	//listFiles();
	
	std::sort(vMovieFiles.begin(), vMovieFiles.end(), sortOp);
	std::sort(vSmiFiles.begin(), vSmiFiles.end(), sortOp);
	
	if(listFiles()!=0)
	{
		std::cout << "Do you want to rename it by movie names(M) or subtitle names(S)? (M/S), otherwise it'll quit." << std::endl;
		char c = std::cin.get();
		
		if(c=='M' || c=='m')
			renameSmiFiles();
		else if(c=='S' || c=='s')
			renameAviFiles();
			
	}
	else{
		std::cout << "quit" << std::endl;
	}
*/
	
	while( (ch = getch()) != KEY_F(10))
	{
		switch(ch)
		{
			case KEY_DOWN:
				{
					mvprintw(2,0,"You pressed Down button");
					break;
				}
		}
	}
	// delete ncurses window
	endwin();

	return 0;
}

void init_scr()
{
	initscr();
	cbreak();

	keypad(stdscr, TRUE);
	noecho();
}
