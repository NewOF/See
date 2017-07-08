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
    post_menu(m_menu);
}

int Waiting(const vector<string>& vec_res)
{
    int key = KEY_RESIZE;
    string::size_type index = 0;

    do {
        switch (key)
        {
        case KEY_DOWN:
            menu_driver(m_menu, REQ_DOWN_ITEM);
            if (index < vec_res.size() - 1)
                ++index;
            break;
        case KEY_UP:
            menu_driver(m_menu, REQ_UP_ITEM);
            if (index != 0)
                --index;
            break;
        case KEY_RESIZE:
            PrintHeadRear();
            break;
        case _KEY_ENTER:
            return index;
        }
        Clear();
        Print(get_file_lines(vec_res[index]));
        refresh();
        key = getch();
    } while (key != _KEY_QUIT && key != _KEY_QUIT2);
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
    for (int i = _DISPLAY_TOP; i < LINES - 1; ++i)
    {
        move(i, 0);
        clrtoeol();
    }
}

void Print(pair<file_name, file_lines> name_line)
{
    int total = LINES - _DISPLAY_TOP - 1;
    if (total <= 0)
        return;
    
    char cmd[1024];
    int lines;
    sscanf(name_line.second.c_str(), "%d", &lines);
    int begin = lines - total / 2 > 0 ? lines - total / 2 : 1;
    int end = begin + total - 1;
    char _cmd[1024];
    snprintf(_cmd, sizeof(_cmd), "echo '%d %d %d' > /tmp/log", end, lines, begin);
    system(_cmd);
    snprintf(cmd, sizeof(cmd), "sed -n '%d,%dp' %s", begin, end, name_line.first.c_str());
    FILE* fp = popen(cmd, "r");
    if (!fp)
    {
        return;
    }
    init_pair(_COL_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(_COL_GREEN, COLOR_GREEN, COLOR_BLACK);
    char buf[1024];
    int index = _DISPLAY_TOP;
    int width = log10(end) + 1;
    int curpos = begin;
    while (fgets(buf, sizeof(buf), fp))
    {
        char line_num[32];
        string str = strip(buf, false);
        snprintf(line_num, sizeof(line_num), "%d", curpos);
        if (curpos == lines)
        {
            wattron(stdscr, COLOR_PAIR( _COL_YELLOW));
            mvprintw(index, 0, "%s%s ", width > strlen(line_num) ? " " : "", line_num);
            mvprintw(index, width + 1, "%s", deltab(str).c_str());
            wattroff(stdscr, COLOR_PAIR( _COL_YELLOW));
        }
        else
        {
            wattron(stdscr, COLOR_PAIR(_COL_GREEN));
            mvprintw(index, 0, "%s%s ", width > strlen(line_num) ? " " : "", line_num);
            wattroff(stdscr, COLOR_PAIR(_COL_GREEN));
            mvprintw(index, width + 1, "%s", deltab(str).c_str());
        }
        ++curpos;
        ++index;
    }
    curs_set(0);
    pclose(fp);
}
void PrintHeadRear()
{
    if (LINES < _DISPLAY_TOP)
        return;
    init_pair(_COL_GREEN, COLOR_GREEN, COLOR_BLACK);
    wattron(stdscr, COLOR_PAIR(_COL_GREEN));
    mvprintw(LINES - 1, 0, "'q' or 'Q' to exit, 'enter' to editor!");
    mvprintw(_DISPLAY_TOP - 1, 1, "%s", string(COLS - 2, '=').c_str());
    wattroff(stdscr, COLOR_PAIR(_COL_GREEN));
}