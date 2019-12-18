#include "curses_util.h"

void init_win_params(WIN *p_win, int y, int x, int w, int h)
{
	// p_win->starty = (LINES - p_win->height) / 2;
	// p_win->startx = (COLS - p_win->width) / 2;
	p_win->starty = y;
	p_win->startx = x;

	if (w != 0)
		p_win->width = w;
	else
		// COLS is y-axis
		p_win->width = COLS - x - 1;

	if (h != 0)
		p_win->height = h;
	else
		// LINES is y-axis
		p_win->height = LINES - y - 1;
}

void create_box(WIN *p_win, bool flag, int colorcode)
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

	if (flag == TRUE)
	{
		mvwprintw(stdscr, y - 1, 0, "Movie Files : %d index1=%d", vMovieFiles.size(), index1);

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
		for (int i = 0; i < size1; i++)
		{
			if (i == index1 && index_inside_movie == TRUE)
			{
				attron(COLOR_PAIR(colorcode));
				mvwprintw(stdscr, y + 1 + i, x + 2, "%s", vMovieFiles[i].c_str());
				attroff(COLOR_PAIR(colorcode));
			}
			else
				mvwprintw(stdscr, y + 1 + i, x + 2, "%s", vMovieFiles[i].c_str());
		}

		// drawing right vertical line
		mvvline(y + 1, x + w, ACS_VLINE, h - 1);
	}
	else
	{
		for (int k = p_win->starty; k <= p_win->starty + p_win->height; k++)
			for (int kk = p_win->startx; kk <= p_win->startx + p_win->width; kk++)
				mvaddch(k, kk, ' ');
		refresh();
	}
}

void create_box2(WIN *p_win, bool flag, int colorcode)
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

	if (flag == TRUE)
	{
		mvwprintw(stdscr, y - 1, 0, "Subtitle Files : %d index2:%d", vSmiFiles.size(), index2);
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
		for (int j = 0; j < size2; j++)
		{
			if (j == index2 && index_inside_movie == FALSE)
			{
				attron(COLOR_PAIR(colorcode));
				mvwprintw(stdscr, y + 1 + j, x + 2, "%s", vSmiFiles[j].c_str());
				attroff(COLOR_PAIR(colorcode));
			}
			else
				mvwprintw(stdscr, y + 1 + j, x + 2, "%s", vSmiFiles[j].c_str());
		}

		// drawing right vertical line
		mvvline(y + 1, x + w, ACS_VLINE, h - 1);
	}
	else
	{
		for (int k = p_win->starty; k <= p_win->starty + p_win->height; k++)
			for (int kk = p_win->startx; kk <= p_win->startx + p_win->width; kk++)
				mvaddch(k, kk, ' ');
		refresh();
	}
}

int print_headline(void)
{
	mvwprintw(stdscr, 0, 0, "Files renamer v1.0");
	mvwprintw(stdscr, 1, 0, "--> renaming subtitles with movies");
	mvwprintw(stdscr, 2, 0, "d:delete, j:down, k:up, y:change");
	mvwprintw(stdscr, 3, 0, "press q to exit");

	return 4;
}

WINDOW *create_win(int height, int width, int starty, int startx, std::string msg)
{
	WINDOW *temp_win;

	temp_win = newwin(height, width, starty, startx);
	box(temp_win, 0, 0);
	mvwprintw(temp_win, 1, 1, "%s", msg.c_str());
	wrefresh(temp_win);
	return temp_win;
}
