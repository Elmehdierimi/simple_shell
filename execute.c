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
