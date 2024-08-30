#include "shell.h"

/**
 * builtin_env - it shows the environ where shell work
 * @data: structure od the data of the program
 * Return: 0 if yes , other nums if no
 */
int builtin_env(data_of_program *data)
{
	char *var_copy = NULL;
	char cpname[50] = {'\0'};
	int s;

	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		for (s = 0; data->tokens[1][s]; s++)
		{
			if (data->tokens[1][s] == '=')
			{
				var_copy = str_duplicate(env_get_key(cpname, data));
				if (var_copy != NULL)
					env_set_key(cpname, data->tokens[1] + s + 1, data);

				/* it prints the environnoment */
				print_environ(data);
				if (env_get_key(cpname, data) == NULL)
				{
					/* it prints var if its not in the environnoment */
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{
					/*the return of the old value*/
					env_set_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[s] = data->tokens[1][s];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - .....
 * @data: structure for the data of the program
 * Return: 0 if yes , other numbers if no
 */
int builtin_set_env(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unset_env - same as well
 * @data: structuew for the data of the program
 * Return: same as up 0 if yes , other nums if no
 */
int builtin_unset_env(data_of_program *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_remove_key(data->tokens[1], data);

	return (0);
}
