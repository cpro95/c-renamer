//============================================================================
// Name        : main.cpp
// Author      : cpro95
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : AVI, SMI Namer by cpro95
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include "utils.h"

typedef struct _WIN_struct {
	int startx, starty;
	int height, width;
} WIN;

void init_win_params(WIN *p_win, int y, int x, int w, int h);
void print_win_params(WIN *p_win);
void create_box(WIN *p_win, bool flag);
void create_box2(WIN *p_win, bool flag);
int print_headline(void);
WINDOW *create_win(int height, int width, int starty, int startx, std::string msg);

std::vector<std::string> vMovieFiles;
std::vector<std::string> vSmiFiles;

static int index1; // index of movie list
static int index2; // index of smi list
static bool index_inside_movie;

int main(int argc, char *argv[])
{
	// initialize varables
	int ch;
	WIN win;	
	WIN win2;
	index1 = 0;
	index2 = 0;
	index_inside_movie=TRUE;
	WINDOW *popup_win;
	
	// init ncurses window
	initscr();
	cbreak();
	//raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);


	if(has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_WHITE);

	// print headline
	int start_line_number = print_headline();

	// load local files.
	loadFiles(".");

	// sorting
	std::sort(vMovieFiles.begin(), vMovieFiles.end(), sortOp);
	std::sort(vSmiFiles.begin(), vSmiFiles.end(), sortOp);
	//std::sort(vTotalFiles.begin(), vTotalFiles.end(), sortOp);

	// listFiles return 0 when no error
	if(listFiles() == 0)
	{

	init_win_params(&win, start_line_number+2, 0, 0, vMovieFiles.size() + 1);
	init_win_params(&win2, start_line_number+3+vMovieFiles.size()+3, 0, 0, vSmiFiles.size() + 1);
	create_box(&win, TRUE);
	create_box2(&win2, TRUE);

	while( (ch = getch()) != 'q')
	{
		switch(ch)
		{

			case 'j':
			case KEY_DOWN:
				{
					create_box(&win, FALSE);
					create_box(&win2, FALSE);

					if(index_inside_movie == TRUE) {
						if(index1 == vMovieFiles.size()-1) {
							index1 = 0;
						} else
						{
							index1++;
						}
					} else {
						if(index2 == vSmiFiles.size()-1) {
							index2 =0;
						} else
						{
							index2++;
						}
					}
					create_box(&win, TRUE);
					create_box2(&win2, TRUE);
					break;
				}
				
			case 'k':
			case KEY_UP:
				{
					create_box(&win, FALSE);
					create_box(&win2, FALSE);

					if(index_inside_movie == TRUE) {
						if(index1 == 0) {
							index1 = vMovieFiles.size()-1;
						} else
						{
							index1--;
						}
					} else {
						if(index2 == 0) {
							index2 = vSmiFiles.size()-1;
						} else
						{
							index2--;
						}
					}
					create_box(&win, TRUE);
					create_box2(&win2, TRUE);
					break;
				}

			case '\t':
			case KEY_BTAB:
				{
					index_inside_movie = !index_inside_movie; 
					create_box(&win, TRUE);
					create_box2(&win2, TRUE);
					break;
				}
			case 'd':
				{
					std::string popup_msg = "delete?(d/esc)";
					popup_win = create_win(3, popup_msg.length()+3, start_line_number+5,(int)COLS/2-popup_msg.length(),popup_msg);
					wrefresh(popup_win);
					
					int ch2;
					while( (ch2=getch()) != 'e')
					{
						switch(ch2)
						{
							case 'd':
							{
								if(index_inside_movie)
								{
									std::vector<std::string>::iterator iter1=vMovieFiles.begin();
								if(vMovieFiles.size()!=1){
									if(index1 == vMovieFiles.size()-1){
										index1--;
									}
									vMovieFiles.erase(iter1 + index1);
								}
								start_line_number = print_headline();
								init_win_params(&win, start_line_number+2, 0, 0, vMovieFiles.size() + 1);
								init_win_params(&win2, start_line_number+3+vMovieFiles.size()+3, 0, 0, vSmiFiles.size() + 1);

								} else
								{
									std::vector<std::string>::iterator iter2=vSmiFiles.begin();
								if(vSmiFiles.size()!=1){
									if(index2 == vSmiFiles.size()-1){
										index2--;
									}
									vSmiFiles.erase(iter2 + index2);
								}
								start_line_number = print_headline();
								init_win_params(&win, start_line_number+2, 0, 0, vMovieFiles.size() + 1);
								init_win_params(&win2, start_line_number+3+vMovieFiles.size()+3, 0, 0, vSmiFiles.size() + 1);

								}
								break;
							}
							case 'e':
							{
								delwin(popup_win);
								break;
							}
						} // switch
						if(ch2 == 'd')
							break;
					} //while

					clear();
					int start_line_number = print_headline();
					create_box(&win, TRUE);
					create_box2(&win2, TRUE);

					break;
				}

		} // switch
	} // while
		
	}
	else
	{
		std::cout << "No files... Bye..." << std::endl;	
		endwin();
		return 1;
	}
	
	// delete ncurses window
	endwin();

	return 0;
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
}

void create_box(WIN *p_win, bool flag)
{
	int i, j;
	// x is x-axis
	// y is y-axis
	// w is width
	// h is height
	// int x, y, w, h;
	
	int x = p_win->startx;
	int y = p_win->starty;
	int w = p_win->width;
	int h = p_win->height;

	if(flag == TRUE)
	{
		mvwprintw(stdscr, y-1,0,"Movie Files : %d index1=%d", vMovieFiles.size(),index1);
	
		// drawing top_left, top_right, bottom_left, bottom_right
		mvaddch(y, x, ACS_ULCORNER);
		mvaddch(y, x + w, ACS_URCORNER);
		mvaddch(y + h, x, ACS_LLCORNER);
		mvaddch(y + h, x + w, ACS_LRCORNER);

		// drawing top, bottom horizontal line 
		mvhline(y, x + 1, ACS_HLINE, w - 1);
		mvhline(y + h, x + 1, ACS_HLINE, w - 1);

		// drawing left vertical line 
		mvvline(y + 1, x, ACS_VLINE, h - 1);

		// drawing movie files list into odd line numbers
		int size1 = vMovieFiles.size();
		for(int i = 0; i < size1; i++)
		{
			if( i == index1 && index_inside_movie == TRUE)
			{
				attron(COLOR_PAIR(2));
				mvwprintw(stdscr, y+1+i, x+2, "%s", vMovieFiles[i].c_str());
				attroff(COLOR_PAIR(2));
			} 
			else
				mvwprintw(stdscr, y+1+i, x+2, "%s", vMovieFiles[i].c_str());
		}

		// drawing right vertical line
		mvvline(y + 1, x + w, ACS_VLINE, h - 1);
	}
	else 
	{
		for(int k = p_win->starty; k <= p_win->starty + p_win->height; k++)
			for(int kk = p_win->startx; kk <= p_win->startx + p_win->width; kk++)
				mvaddch(k, kk, ' ');
		refresh();
	}
}

void create_box2(WIN *p_win, bool flag)
{
	int i, j;
	// x is x-axis
	// y is y-axis
	// w is width
	// h is height
	// int x, y, w, h;
	
	int x = p_win->startx;
	int y = p_win->starty;
	int w = p_win->width;
	int h = p_win->height;

	if(flag == TRUE)
	{
		mvwprintw(stdscr,y-1,0,"Subtitle Files : %d index2:%d", vSmiFiles.size(),index2);
		// drawing top_left, top_right, bottom_left, bottom_right
		mvaddch(y, x, ACS_ULCORNER);
		mvaddch(y, x + w, ACS_URCORNER);
		mvaddch(y + h, x, ACS_LLCORNER);
		mvaddch(y + h, x + w, ACS_LRCORNER);

		// drawing top, bottom horizontal line 
		mvhline(y, x + 1, ACS_HLINE, w - 1);
		mvhline(y + h, x + 1, ACS_HLINE, w - 1);

		// drawing left vertical line 
		mvvline(y + 1, x, ACS_VLINE, h - 1);

		int size2 = vSmiFiles.size();
		for(int j = 0; j < size2; j++)
		{
			if( j == index2 && index_inside_movie == FALSE)
			{
				attron(COLOR_PAIR(2));
				mvwprintw(stdscr, y+1+j, x+2, "%s", vSmiFiles[j].c_str());
				attroff(COLOR_PAIR(2));
			}
			else
				mvwprintw(stdscr, y+1+j, x+2, "%s", vSmiFiles[j].c_str());
		}

		// drawing right vertical line
		mvvline(y + 1, x + w, ACS_VLINE, h - 1);
	}
	else 
	{
		for(int k = p_win->starty; k <= p_win->starty + p_win->height; k++)
			for(int kk = p_win->startx; kk <= p_win->startx + p_win->width; kk++)
				mvaddch(k, kk, ' ');
		refresh();
	}
}

int print_headline(void)
{
	mvwprintw(stdscr,0,0,"Files renamer v1.0");
	mvwprintw(stdscr,1,0,"--> renaming subtitles with movies");
	mvwprintw(stdscr,2,0,"List of movies & subtitles files.");
	mvwprintw(stdscr,3,0,"press q to exit");

	return 4;

}

WINDOW *create_win(int height, int width, int starty, int startx, std::string msg)
{
	WINDOW *temp_win;

	temp_win = newwin(height, width, starty, startx);
	box(temp_win, 0, 0);
	mvwprintw(temp_win, 1 , 1 , "%s", msg.c_str());
	wrefresh(temp_win);
	return temp_win;
}
