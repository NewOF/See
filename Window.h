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
static ITEM** m_items;
static MENU* m_menu;


void CreateMenu(const vector<string>& option);
void Waiting(const int size, int& index);
void CloseMenu();
