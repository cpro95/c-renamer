#include <ncurses.h>
#include <string>
#include <vector>

typedef struct _WIN_struct {
	int startx, starty;
	int height, width;
} WIN;

void init_win_params(WIN *p_win, int y, int x, int w, int h);
void print_win_params(WIN *p_win);
void create_box(WIN *p_win, bool flag, int colorcode);
void create_box2(WIN *p_win, bool flag,int colorcode);
int print_headline(void);
WINDOW *create_win(int height, int width, int starty, int startx, std::string msg);

// extern global variable
extern std::vector<std::string> vMovieFiles;
extern std::vector<std::string> vSmiFiles;

extern int index1; // index of movie list
extern int index2; // index of smi list
extern bool index_inside_movie;


