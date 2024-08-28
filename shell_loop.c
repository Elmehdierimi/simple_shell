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
