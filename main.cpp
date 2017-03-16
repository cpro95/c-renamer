//============================================================================
// Name        : main.cpp
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

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);

int main(int argc, char *argv[])
{
	// initialize varables
	int ch;
	
	// init ncurses window
	initscr();
	// cbreak();
	raw();
	keypad(stdscr, TRUE);
	noecho();

	if(has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_WHITE);
	mvwprintw(stdscr,0,0,"Press F1 or F2 to change color of text\nF10 to exit");

	while( (ch = getch()) != KEY_F(10)) 
	{
		switch(ch)
		{
			case KEY_F(1):
			{
				attron(COLOR_PAIR(1));
				print_in_middle(stdscr, LINES / 2 , 0, 0, "Viola !!! In color number 1 ...");
				attroff(COLOR_PAIR(1));
				break;
			}
			case KEY_F(2):
			{
				attron(COLOR_PAIR(2));
				print_in_middle(stdscr, LINES / 2 , 0, 0, "Viola !!! In color number 2...");
				attroff(COLOR_PAIR(2));
				break;
			}

		}
	}

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
	
	// delete ncurses window
	endwin();

	return 0;
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string)
{
	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;

	getyx(win,y,x);

	if(startx != 0)
		x = startx;

	if(starty != 0)
		y = starty;

	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length) / 2;
	x = startx + (int)temp;

	mvwprintw(win, y, x, "%s", string);
	refresh();
}
