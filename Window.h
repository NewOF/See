#pragma once
#include "utils.h"
#include <menu.h>
#include <ncurses.h>

#define  _KEY_ENTER     0012
#define  _KEY_ESC	    0033
#define  _KEY_QUIT	    0161
#define  _KEY_QUIT2     0121

#define _DISPLAY_TOP 17

#define _COL_BLACK	    0
#define _COL_RED	    1
#define _COL_GREEN	    2
#define _COL_YELLOW	    3
#define _COL_BLUE	    4
#define _COL_MAGENTA	5
#define _COL_CYAN	    6
#define _COL_WHITE	    7


void CreateMenu(const vector<string>& option);
int Waiting(const vector<string>& vec_res);
void CloseMenu();
void Print(pair<file_name, file_lines> name_line);
void PrintHeadRear();
void Clear();
