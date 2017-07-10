#include "Window.h"

const char* fmt[2] =
{
	"find %s -type f %s|xargs grep -nE '([^[:alnum:]_]%s[^[:alnum:]_]|^%s$|[^[:alnum:]_]%s$|^%s[^[:alnum:]_])'",
	"find %s -type f %s|xargs grep -n %s"
};

int main(int argc, char** argv) 
{
	string target;
	string path = "";
	int enhence = 0;
	if (!get_arg(argc, argv, target, path, enhence))
	{
		return -1;
	}
	if (!get_filter())
	{
		return -1;
	}
	
	string options = "";
	combining(options);

	char search_cmd[1024];
	if (enhence == 0)
		snprintf(search_cmd, sizeof(search_cmd), fmt[enhence], path.c_str(), options.c_str(),
			target.c_str(), target.c_str(), target.c_str(), target.c_str());
	else
		snprintf(search_cmd, sizeof(search_cmd), fmt[enhence], path.c_str(), options.c_str(), target.c_str());
	
	vector<string> vec_res;
	if (!run_cmd(vec_res, search_cmd))
	{
		return -1;
	}
	if (vec_res.size() > 0)
	{
		CreateMenu(vec_res);
		int index = Waiting(vec_res);
		CloseMenu();
		if (index != -1)
		{
			pair<string,string> pair = get_file_lines(vec_res[index]);
			system(string("vim " + pair.first + " +" + pair.second).c_str());;
		}
	}
	
	return 0;
}