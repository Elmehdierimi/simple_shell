#include "shell.h"

/**
 * tokenize - splits the input line into tokens using delimiters
 * @prog_data: a pointer to the program's data
 *
 * Return: nothing, sets tokens in prog_data
 */
void tokenize(data_of_program *prog_data)
{
	char *delim = " \t";
	int idx1, idx2, num_tokens = 2, len;

	len = str_length(prog_data->input_line);
	if (len > 0 && prog_data->input_line[len - 1] == '\n')
	{
		prog_data->input_line[len - 1] = '\0';
	}

	for (idx1 = 0; prog_data->input_line[idx1]; idx1++)
	{
		for (idx2 = 0; delim[idx2]; idx2++)
		{
			if (prog_data->input_line[idx1] == delim[idx2])
			{
				num_tokens++;
			}
		}
	}

	prog_data->tokens = malloc(num_tokens * sizeof(char *));
	if (prog_data->tokens == NULL)
	{
		perror(prog_data->program_name);
		exit(errno);
	}

	idx1 = 0;
prog_data->tokens[idx1] = str_duplicate(_strtok(prog_data->input_line, delim));
	prog_data->command_name = str_duplicate(prog_data->tokens[0]);

	while (prog_data->tokens[idx1])
	{
		prog_data->tokens[++idx1] = str_duplicate(_strtok(NULL, delim));
	}
}
