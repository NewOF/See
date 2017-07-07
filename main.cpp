#include "Window.h"

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
		int index = -1;
		Waiting(vec_res.size(), index);
		CloseMenu();
		if (index != -1)
		{
			string str = vec_res[index];
			string::size_type pos = str.find(':');
			string cmd = "vim " + str.substr(0, pos);
			cmd += " +" + str.substr(pos + 1, str.find(':', pos + 1) - pos);
			system(cmd.c_str());
		}
	}
	
	return 0;
}