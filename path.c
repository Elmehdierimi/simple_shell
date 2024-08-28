#include "shell.h"

/**
 * is_executable - checks if the given path is an executable file
 * @info: pointer to the info structure
 * @filepath: path to the file
 *
 * Return: 1 if the file is executable, 0 otherwise
 */
int is_executable(info_t *info, char *filepath)
{
	struct stat file_stat;

	(void)info;
	if (!filepath || stat(filepath, &file_stat) != 0)
		return (0);

	if (file_stat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * copy_chars - copies characters from a string within a specified range
 * @path_string: the PATH string
 * @start: starting index for copying
 * @end: stopping index for copying
 *
 * Return: pointer to a new buffer containing the copied characters
 */
char *copy_chars(char *path_string, int start, int end)
{
	static char buffer[1024];
	int i, j = 0;

	for (i = start; i < end; i++)
	{
		if (path_string[i] != ':')
			buffer[j++] = path_string[i];
	}
	buffer[j] = '\0';
	return (buffer);
}

/**
 * locate_command - searches for a command in the PATH string
 * @info: pointer to the info structure
 * @path_string: the PATH string
 * @command: the command to locate
 *
 * Return: full path of the command if found, or NULL
 */
char *locate_command(info_t *info, char *path_string, char *command)
{
	int i = 0, start_index = 0;
	char *full_path;

	if (!path_string)
		return (NULL);
	if (_strlen(command) > 2 && starts_with(command, "./"))
	{
		if (is_executable(info, command))
			return (command);
	}
	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			full_path = copy_chars(path_string, start_index, i);
			if (*full_path == '\0')
				_strcat(full_path, command);
			else
			{
				_strcat(full_path, "/");
				_strcat(full_path, command);
			}
			if (is_executable(info, full_path))
				return (full_path);
			if (!path_string[i])
				break;
			start_index = i + 1;
		}
		i++;
	}
	return (NULL);
}

