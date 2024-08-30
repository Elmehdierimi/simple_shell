#include "shell.h"

/**
 * expand_variables - expand variables
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_variables(data_of_program *data)
{
	int s, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (s = 0; line[s]; s++)
		if (line[s] == '#')
			line[s--] = '\0';
		else if (line[s] == '$' && line[s + 1] == '?')
		{
			line[s] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + s + 2);
		}
		else if (line[s] == '$' && line[s + 1] == '$')
		{
			line[s] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + s + 2);
		}
		else if (line[s] == '$' && (line[s + 1] == ' ' || line[s + 1] == '\0'))
			continue;
		else if (line[s] == '$')
		{
			for (j = 1; line[s + j] && line[s + j] != ' '; j++)
				expansion[j - 1] = line[s + j];
			temp = env_get_key(expansion, data);
			line[s] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + s + j);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - expans aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_alias(data_of_program *data)
{
	int x, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (x = 0; line[x]; x++)
	{
		for (j = 0; line[x + j] && line[x + j] != ' '; j++)
			expansion[j] = line[x + j];
		expansion[j] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + x + j);
			line[x] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but sets errno.
 */
int buffer_add(char *buffer, char *str_to_add)
{
	int length, x;

	length = str_length(buffer);
	for (x = 0; str_to_add[x]; x++)
	{
		buffer[length + x] = str_to_add[x];
	}
	buffer[length + x] = '\0';
	return (length + x);
}
