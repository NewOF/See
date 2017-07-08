#include "Window.h"

ITEM** m_items;
MENU* m_menu;

void CreateMenu(const vector<string>& options)
{
	initscr();
	cbreak();
	noecho();
	start_color();
	keypad(stdscr, TRUE);
	m_items = new ITEM*[options.size() + 1];
	int index = 0;
	for (auto iter = options.begin(); iter != options.end(); ++iter)
		m_items[index++] = new_item("+", iter->c_str());
	
	m_items[index] = (ITEM *)nullptr;

	m_menu = new_menu((ITEM **)m_items);
	init_pair(_COL_GREEN, COLOR_GREEN, COLOR_BLACK);
	wattron(stdscr, COLOR_PAIR(_COL_GREEN));
	mvprintw(LINES - 1, 0, "'q' to exit!");
	mvprintw(_DISPLAY_TOP - 1, 1, "%s", string(COLS - 2, '=').c_str());
	post_menu(m_menu);
	wattroff(stdscr, COLOR_PAIR(_COL_GREEN));
	refresh();
}

int Waiting(const vector<string>& vec_res)
{
	int key;
	string::size_type index = 0;
	Print(get_file_lines(vec_res[index]));
	refresh();
	while ((key = getch()) != _KEY_QUIT)
	{
		switch (key)
		{
		case KEY_DOWN:
			menu_driver(m_menu, REQ_DOWN_ITEM);
			if (index < vec_res.size() - 1)
			{
				++index;
				Clear();
				Print(get_file_lines(vec_res[index]));
				refresh();
			}
			break;
		case KEY_UP:
			menu_driver(m_menu, REQ_UP_ITEM); 
			if (index != 0)
			{
				--index;
				Clear();
				Print(get_file_lines(vec_res[index]));
				refresh();
			}
			break;
		case _KEY_ENTER:	
			return index;
		}
	}
	return -1;
}

void CloseMenu()
{
	int index = 0;
	if (m_items[index])
		free_item(m_items[index++]);
	free_menu(m_menu);
	endwin();
}

void Clear()
{
	for (int i = _DISPLAY_TOP; i < LINES - 2; ++i)
	{
		move(i, 0);
		clrtoeol();
	}
}

void Print(pair<file_name, file_lines> name_line)
{
	int total = LINES - _DISPLAY_TOP - 2;
	if (total < 1)
		return;
	
	char cmd[1024];
	int lines;
	sscanf(name_line.second.c_str(), "%d", &lines);
	int pos = lines - total / 2 > 0 ? lines - total / 2 : 1;
	snprintf(cmd, sizeof(cmd), "sed -n '%d,%dp' %s", pos,	lines + total / 2, name_line.first.c_str());
	FILE* fp = popen(cmd, "r");
	if (!fp)
	{
		return;
	}
	init_pair(_COL_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(_COL_WHITE, COLOR_WHITE, COLOR_BLACK);
	char buf[1024];
	int index = _DISPLAY_TOP;
	int sign = 0;
	while (fgets(buf, sizeof(buf), fp))
	{
		char tmp_str[1024];
		string str = strip(buf, false);
		snprintf(tmp_str, sizeof(tmp_str), "%s%d %s", sign ? "" : " ", pos, del_tab(str).c_str());
		if (int(log10(pos)) + 1 == int(log10(pos + 1)))
			sign = 1;
		wattron(stdscr, COLOR_PAIR(pos == lines ? _COL_MAGENTA : _COL_WHITE));
		mvprintw(index++, 0, "%s", tmp_str);
		wattroff(stdscr, COLOR_PAIR(pos == lines ? _COL_MAGENTA : _COL_WHITE));
		++pos;
	}
	curs_set(0);
	pclose(fp);
}