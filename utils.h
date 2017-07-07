#pragma once
#include <cstdlib>
#include <map>
#include <string>
#include <cstring>
#include <vector>
#include <cstdio>
#include <iostream>
#include <unistd.h>

#define NAME  "name"
#define NAME_IG  "name_ignore"
#define DIR_IG   "dir_ignore"
#define PERM  "perm"


using namespace std;

static const char* fmt[2] =
{
	"find %s -type f %s|xargs grep -nE '([^[:alnum:]_]%s[^[:alnum:]_]|^%s$|[^[:alnum:]_]%s$|^%s[^[:alnum:]_])'",
	"find %s -type f %s|xargs grep -n %s" 
};
const char filter_file[] = "/etc/search/filter.conf";
static map<string, string> map_filter;

string strip(string str);
bool get_filter();
bool combining(string& options);
bool get_arg(int& argc, char** argv, string& target, string& path, int& enhence);
bool run_cmd(vector<string>& res, char* cmd);
void usage();