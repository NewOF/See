#pragma once
#include "utils.h"
#include <menu.h>
#ifdef __linux__
#include <curses.h>
#elif __CYGWIN__
#include <ncurses.h>
#endif

#define  _KEY_ENTER 0012
#define  _KEY_ESC	0033
#define  _KEY_QUIT	0161

#define _DISPLAY_TOP 17

#define _COL_MAGENTA	1
#define _COL_WHITE		2 
#define _COL_RED		3
#define _COL_GREEN		4
 

void CreateMenu(const vector<string>& option);
int Waiting(const vector<string>& vec_res);
void CloseMenu();
void Print(pair<file_name, file_lines> name_line);
void Clear();
