#include "shell.h"
/**
 * execute - function that execute a command with the vars of the path
 * @data: pointer to the data of the program
 * Return: 0 if yes else -1
 */
int execute(data_of_program *data)
{
	/*refers to status and retreval*/
	int s;
	int r = 0;
	pid_t pidd;

	r = builtins_list(data);
	if (r != -1)
		return (r);

	r = find_program(data);
	if (r)
	{
		return (r);/* if program is not found */
	}
	else/* if program here was found then we will keep up*/
	{

		pidd = fork();
		if (pidd == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			/*execute of the program*/
			r = execve(data->tokens[0], data->tokens, data->env);
			if (r == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&s);
			if (WIFEXITED(s))/*check the exit status*/
				errno = WEXITSTATUS(s);
			else if (WIFSIGNALED(s))
				errno = 128 + WTERMSIG(s);
		}
	}
	return (0);
}
