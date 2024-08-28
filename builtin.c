#include "shell.h"

/**
 * find_builtin - locate and execute a built-in command
 * @info: structure containing shell info and status
 *
 * Return: -1 if command not found,
 *         0 if command executed successfully,
 *         1 if command found but execution failed,
 *         -2 if command indicates shell exit
 */
int find_builtin(info_t *info)
{
	int index = 0;
	int result = -1;
	builtin_table builtins[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	while (builtins[index].type != NULL)
	{
		if (_strcmp(info->argv[0], builtins[index].type) == 0)
		{
			info->line_count++;
			result = builtins[index].func(info);
			break;
		}
		index++;
	}

	return (result);
}
