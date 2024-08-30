#include "shell.h"

/**
 * builtins_list - function that search for the match and execute
 * @data: structure of the data of the program
 * Return: if the function executed is a match then yes, else -1
 **/
int builtins_list(data_of_program *data)
{
	int s;/*s is basically the interator*/
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

	for (s = 0; options[s].builtin != NULL; s++)
	{
		if (str_compare(options[s].builtin, data->command_name, 0))
		{
			return (options[s].function(data));
		}
	}
	return (-1);/*if no match than return the -1*/
}
