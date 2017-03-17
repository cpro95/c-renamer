//============================================================================
// Name        : main.cpp
// Author      : cpro95
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : AVI, SMI Namer by cpro95
//============================================================================

#include <iostream>
#include <string>
#include <ncurses.h>
#include "utils.h"

// global variables
std::vector<std::string> vMovieFiles;
std::vector<std::string> vSmiFiles;

typedef struct _win_border_struct {
	chtype ls, rs, ts, bs,
		   tl, tr, bl, br;
} WIN_BORDER;

typedef struct _WIN_struct {
	int startx, starty;
	int height, width;
	WIN_BORDER border;
} WIN;

void init_win_params(WIN *p_win, int y, int x, int w, int h);
void print_win_params(WIN *p_win);
void create_box(WIN *p_win, bool flag);
void delete_box(WIN *p_win);

void print_in_middle(WINDOW *win, int starty, int startx, int width, std::string string);

int main(int argc, char *argv[])
{
	// initialize varables
	int ch;
	WIN win;	
	
	// init ncurses window
	initscr();
	// cbreak();
	raw();
	keypad(stdscr, TRUE);
	noecho();

	// Initialize the window parameters
	init_win_params(&win, 5 , 0 , 0, 0);

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
				print_in_middle(stdscr, LINES / 2 , 20, 10, "Viola !!! In color number 1 ...");
				attroff(COLOR_PAIR(1));
				break;
			}
			case KEY_F(2):
			{
				attron(COLOR_PAIR(2));
				print_in_middle(stdscr, LINES / 2 + 2, 20, 10, "Viola !!! In color number 2...");
				attroff(COLOR_PAIR(2));
				break;
			}
			case KEY_F(3):
			{
				attron(COLOR_PAIR(2));
				wmove(stdscr, 10,0);
				waddch(stdscr, '3');
				attroff(COLOR_PAIR(2));
				break;
			}
			case KEY_F(4):
			{
				create_box(&win, TRUE);
				break;
			}
			case KEY_F(5):
			{
				delete_box(&win);
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

void print_in_middle(WINDOW *win, int starty, int startx, int width, std::string str)
{
	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;

	getyx(win,y,x);

	if(starty != 0)
		y = starty;

	if(startx != 0)
		x = startx;

	if(width == 0)
		width = 80;

	length = str.length();
	temp = (width - length) / 2;
	x = startx + (int)temp;

	mvwprintw(win, y, x, "%s", str.c_str());
	refresh();
}

void init_win_params(WIN *p_win, int y, int x, int w, int h)
{
	// p_win->starty = (LINES - p_win->height) / 2;
	// p_win->startx = (COLS - p_win->width) / 2;
	p_win->starty = y;
	p_win->startx = x;

	if(w != 0)
		p_win->width = w;
	else
		// COLS is y-axis
		p_win->width = COLS - x - 1;
	
	if(h != 0)
		p_win->height = h;
	else
		// LINES is y-axis
		p_win->height = LINES - y - 1;

	p_win->border.ls = '|';
	p_win->border.rs = '|';
	p_win->border.ts = '-';
	p_win->border.bs = '-';
	p_win->border.tl = '+';
	p_win->border.tr = '+';
	p_win->border.bl = '+';
	p_win->border.br = '+';
}

void create_box(WIN *p_win, bool flag)
{
	int i, j;
	// x is x-axis
	// y is y-axis
	// w is width
	// h is height
	int x, y, w, h;
	
	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;

	if(flag == TRUE)
	{
		mvaddch(y, x, p_win->border.tl);
		mvaddch(y, x + w, p_win->border.tr);
		mvaddch(y + h, x, p_win->border.bl);
		mvaddch(y + h, x + w, p_win->border.br);

		mvhline(y, x + 1, p_win->border.ts, w - 1);
		mvhline(y + h, x + 1, p_win->border.bs, w - 1);

		mvvline(y + 1, x, p_win->border.ls, h - 1);
		mvvline(y + 1, x + w, p_win->border.rs, h - 1);
	}
}

void delete_box(WIN *p_win)
{
	for(int j = p_win->starty; j <= p_win->starty + p_win->height; j++)
		for(int i = p_win->startx; i <= p_win->startx + p_win->width; i++)
			mvaddch(j, i, ' ');
	refresh();
}
