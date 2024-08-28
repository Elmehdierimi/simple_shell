#include "shell.h"

/**
 * find_command - search for and execute a command from PATH
 * @info: structure containing shell info and status
 *
 * Return: void
 */
void find_command(info_t *info)
{
	char *command_path = NULL;
	int i = 0, non_delim_count = 0;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
		info->line_count++;
		info->linecount_flag = 0;

	while (info->arg[i])
	{
		if (!is_delim(info->arg[i], " \t\n"))
			non_delim_count++;
		i++;
	}

	if (non_delim_count == 0)
		return;

	command_path = find_path(info, _getenv(info, "PATH="), info->argv[0]);

	if (command_path)
	{
		info->path = command_path;
		execute_command(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
		{
			execute_command(info);
		}
		else if (*(info->arg) != '\n')
			info->status = 127;
			print_error(info, "not found\n");
	}
}
