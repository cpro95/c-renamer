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
#include "curses_util.h"
#include "utils.h"

// global variable
std::vector<std::string> vMovieFiles;
std::vector<std::string> vSmiFiles;

int index1; // index of movie list
int index2; // index of smi list
bool index_inside_movie;

int main(int argc, char *argv[])
{
	//initialize global variable
	index1=0; // index of movie list
	index2=0; // index of smi list
	index_inside_movie=TRUE;

	// initialize varables
	int ch;
	WIN win;	
	WIN win2;
	WINDOW *popup_win;
	
	// init ncurses window
	initscr();
	cbreak();
	//raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	if(has_colors() == FALSE) { endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);

	// print headline
	int start_line_number = print_headline();

	// load local files.
	loadFiles(".");

	// sorting
	std::sort(vMovieFiles.begin(), vMovieFiles.end(), sortOp);
	std::sort(vSmiFiles.begin(), vSmiFiles.end(), sortOp);

	// listFiles return 0 when no error
	if(listFiles() == 0)
	{

	init_win_params(&win, start_line_number+2, 0, 0, vMovieFiles.size() + 1);
	init_win_params(&win2, start_line_number+3+vMovieFiles.size()+3, 0, 0, vSmiFiles.size() + 1);
	create_box(&win, TRUE,1);
	create_box2(&win2, TRUE,1);

	while( (ch = getch()) != 'q')
	{
		switch(ch)
		{

			case 'j':
			case KEY_DOWN:
				{
					create_box(&win, FALSE,1);
					create_box(&win2, FALSE,1);

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
					create_box(&win, TRUE,1);
					create_box2(&win2, TRUE,1);
					break;
				}
				
			case 'k':
			case KEY_UP:
				{
					create_box(&win, FALSE,1);
					create_box(&win2, FALSE,1);

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
					create_box(&win, TRUE,1);
					create_box2(&win2, TRUE,1);
					break;
				}

			case '\t':
			case KEY_BTAB:
				{
					index_inside_movie = !index_inside_movie; 
					create_box(&win, TRUE,1);
					create_box2(&win2, TRUE,1);
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
										vMovieFiles.erase(iter1 + index1);
										index1--;
									} else
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
										vSmiFiles.erase(iter2 + index2);
										index2--;
									} else
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
					create_box(&win, TRUE,1);
					create_box2(&win2, TRUE,1);

					break;
				} // case d

			case ' ': //case space for selection to move
				{
					
					create_box(&win, TRUE,2);
					create_box2(&win2, TRUE,2);
					wrefresh(stdscr);

					std::string popup_msg = "down/up/esc?(j/k/e)";
					popup_win = create_win(3, popup_msg.length()+3, start_line_number+5,(int)COLS/2-popup_msg.length()/2,popup_msg);
					wrefresh(popup_win);
					
					int ch3;
					while( (ch3=getch()) != 'e')
					{
						switch(ch3)
						{
							case 'j':
							case KEY_DOWN:
							{
								swapVector(true);
								break;
							}
							case 'k':
							case KEY_UP:
							{
								swapVector(false);
								break;
							}
							case 'e':
							{
								delwin(popup_win);
								break;
							}
						} // end of switch	
						
					if(ch3 == 'j' || ch3 == 'k' || ch3 == KEY_DOWN || ch3 == KEY_UP)
						break;
					} // while

					clear();
					int start_line_number = print_headline();
					create_box(&win, TRUE,1);
					create_box2(&win2, TRUE,1);

					break; //end of case space
				} // case space

			case 'y':
				{

					// if counts are mismatched
					if(vMovieFiles.size() != vSmiFiles.size())
					{
						std::string popup_msg = "Mismatch Error! (e)";
						popup_win = create_win(3, popup_msg.length()+3, start_line_number+5,(int)COLS/2-popup_msg.length()/2,popup_msg);
						wrefresh(popup_win);

						int ch5;
						while ( (ch5=getch()) != 'e')
						{
							switch(ch5)
							{
								case 'e':
								{
									delwin(popup_win);
									break;
								}
							}
							if(ch5 == 'e')
								break;
						}

						clear();
						int start_line_number = print_headline();
						create_box(&win, TRUE,1);
						create_box2(&win2, TRUE,1);
						break;
					} // end of if statement = counts are mismatched

					std::string popup_msg = "confirm?(m)ovies (s)ubtitle(m/s/e)";
					popup_win = create_win(3, popup_msg.length()+3, start_line_number+5,(int)COLS/2-popup_msg.length()/2,popup_msg);
					wrefresh(popup_win);
					
					int ch4;
					while( (ch4=getch()) != 'e')
					{
						switch(ch4)
						{
							case 'm':
							{
								int err = renameSmiFiles();
								std::cout << "err: " << err << std::endl;
								break;
							}
							case 's':
							{
								int err = renameAviFiles();
								std::cout << "err: " << err << std::endl;
								break;
							}
							case 'e':
							{
								delwin(popup_win);
								break;
							}
						} // end of switch	
					if(ch4 == 'm' || ch4 == 's')
						break;
					} // while

					// rename it then files reloading
					// load local files.
					loadFiles(".");

					// sorting
					std::sort(vMovieFiles.begin(), vMovieFiles.end(), sortOp);
					std::sort(vSmiFiles.begin(), vSmiFiles.end(), sortOp);

					clear();
					init_win_params(&win, start_line_number+2, 0, 0, vMovieFiles.size() + 1);
					init_win_params(&win2, start_line_number+3+vMovieFiles.size()+3, 0, 0, vSmiFiles.size() + 1);
					int start_line_number = print_headline();
					create_box(&win, TRUE,1);
					create_box2(&win2, TRUE,1);

					break; // end of case y
				} // case y
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
} //end of main



