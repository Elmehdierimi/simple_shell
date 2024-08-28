#include "shell.h"

/**
 * shell_loop - main loop for the shell
 * @info: structure containing shell info and status
 * @argv: argument vector from main()
 *
 * Return: 0 on success, 1 on error, or other error codes
 */
int shell_loop(info_t *info, char **argv)
{
	ssize_t read_status = 0;
	int built_in_status = 0;

	while (read_status != -1 && built_in_status != -2)
	{
		clear_info(info);
		if (interactive(info))
		{
			_puts("$ ");
		}

		_eputchar(BUF_FLUSH);
		read_status = get_input(info);

		if (read_status != -1)

			set_info(info, argv);
			built_in_status = find_builtin(info);
			if (built_in_status == -1)
			{
				find_command(info);
			}
		}
		else if (interactive(info))
		{
			_putchar('\n');
		}
		free_info(info, 0);
	}

	write_history(info);
	free_info(info, 1);

	if (!interactive(info) && info->status)
	{
		exit(info->status);
	}

	if (built_in_status == -2)
	{
		if (info->err_num == -1)
		{
			exit(info->status);
		}
		exit(info->err_num);
	}

	return (built_in_status);
}

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
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	while (info->arg[i])
	{
		if (!is_delim(info->arg[i], " \t\n"))
		{
			non_delim_count++;
		}
		i++;
	}

	if (non_delim_count == 0)
	{
		return;
	}

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
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * execute_command - create a new process to execute a command
 * @info: structure containing shell info and status
 *
 * Return: void
 */
void execute_command(info_t *info)
{
	pid_t process_id;

	process_id = fork();

	if (process_id == -1)
	{
		perror("Error:");
		return;
	}

	if (process_id == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);

			if (errno == EACCES)
			{
				exit(126);
			}

			exit(1);
		}
	}
	else
	{
		wait(&(info->status));

		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);

			if (info->status == 126)
			{
				print_error(info, "Permission denied\n");
			}
		}
	}
}
