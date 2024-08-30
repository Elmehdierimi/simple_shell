#include "shell.h"
/**
 * tokenize - it separate the str with designed delimiter
 * @data: that pointer
 * Return: array
 */
void tokenize(data_of_program *data)
{
	char *delimit = " \t";
	int s, r;
	int counter = 2;
	int len;/*this is the lenght*/

	len = str_length(data->input_line);
	if (len)
	{
		if (data->input_line[len - 1] == '\n')
			data->input_line[len - 1] = '\0';
	}

	for (s = 0; data->input_line[s]; s++)
	{
		for (r = 0; delimit[r]; r++)
		{
			if (data->input_line[s] == delimit[s])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	s = 0;
	data->tokens[s] = str_duplicate(_strtok(data->input_line, delimit));
	data->command_name = str_duplicate(data->tokens[0]);
	while (data->tokens[s++])
	{
		data->tokens[s] = str_duplicate(_strtok(NULL, delimit));
	}
}
