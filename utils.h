#pragma once
#include <cstdlib>
#include <map>
#include <string>
#include <cstring>
#include <vector>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cmath>

#define NAME  "name"
#define NAME_IG  "name_ignore"
#define DIR_IG   "dir_ignore"
#define PERM  "perm"

using namespace std;

typedef string file_name;
typedef string file_lines;
typedef char*  m_string;

string strip(string str, bool del_left);
string& deltab(string& str);

bool get_filter();
bool combining(string& options);
bool get_arg(int& argc, char** argv, string& target, string& path, int& enhence);
bool run_cmd(vector<string>& res, char* cmd);
void usage();
pair<file_name, file_lines> get_file_lines(string str);