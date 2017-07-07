#include "Window.h"

//Create a window from point p;
void CreateMenu(const vector<string>& options)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	m_items = new ITEM*[options.size() + 1];
	int index = 0;
	for (auto iter = options.begin(); iter != options.end(); ++iter)
		m_items[index++] = new_item("+", iter->c_str());
	
	m_items[index] = (ITEM *)nullptr;

	m_menu = new_menu((ITEM **)m_items);
	mvprintw(LINES - 2, 0, "'q' to exit!");
	post_menu(m_menu);
	refresh();
}

void Waiting(const int size, int& index)
{
	int key;
	index = 0;
	while ((key = getch()) != _KEY_QUIT)
	{
		switch (key)
		{
		case KEY_DOWN:
			if(index < item_count(m_menu) - 1)
				++index;
			menu_driver(m_menu, REQ_DOWN_ITEM);
			break;
		case KEY_UP:
			if (index != 0)
				--index;
			menu_driver(m_menu, REQ_UP_ITEM);
			break;
		case _KEY_ENTER:	
			return;
		}
	}
	index = -1;
}

void CloseMenu()
{
	int index = 0;
	if (m_items[index])
		free_item(m_items[index++]);
	free_menu(m_menu);
	endwin();
}