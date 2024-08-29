#include "shell.h"

/**
 * _getline - read one line from the prompt.
 * @data: struct for the program's data
 *
 * Return: reading counting bytes.
 */
int _getline(data_of_program *data)
{
	char buffer[BUFFER_SIZE] = {'\0'};
	static char *commands_array[10] = {NULL};
	static char operators_array[10] = {'\0'};
	ssize_t bytes_read = 0;
	int i = 0;

	/* Check if there are no more commands in the array */
	if (!commands_array[0] ||
		(operators_array[0] == '&' && errno != 0) ||
		(operators_array[0] == '|' && errno == 0))
	{
		/* Free the memory allocated in the array if it exists */
		for (i = 0; commands_array[i]; i++)
		{
			free(commands_array[i]);
			commands_array[i] = NULL;
		}

		/* Read from the file descriptor into the buffer */
		bytes_read = read(data->file_descriptor, buffer, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/* Split lines by '\n' or ';' */
		i = 0;
		do {
			commands_array[i] = str_duplicate(_strtok(i ? NULL : buffer, "\n;"));
			/* Check and split for '&&' and '||' operators */
			i = check_logic_ops(commands_array, i, operators_array);
		} while (commands_array[i++]);
	}

	data->input_line = commands_array[0];
	for (i = 0; commands_array[i]; i++)
	{
		commands_array[i] = commands_array[i + 1];
		operators_array[i] = operators_array[i + 1];
	}

	return (str_length(data->input_line));
}

/**
 * check_logic_ops - checks and splits for '&&' and '||' operators
 * @commands_array: array of the commands
 * @i: index in the commands_array to be checked
 * @operators_array: array of the logical operators for each previous command
 *
 * Return: index of the last command in the commands_array.
 */
int check_logic_ops(char *commands_array[], int i, char operators_array[])
{
	char *temp = NULL;
	int j = 0;

	/* Check for the '&' character in the command line */
	for (j = 0; commands_array[i] != NULL && commands_array[i][j]; j++)
	{
		if (commands_array[i][j] == '&' && commands_array[i][j + 1] == '&')
		{
			/* Split the line when '&&' is found */
			temp = commands_array[i];
			commands_array[i][j] = '\0';
			commands_array[i] = str_duplicate(commands_array[i]);
			commands_array[i + 1] = str_duplicate(temp + j + 2);
			i++;
			operators_array[i] = '&';
			free(temp);
			j = 0;
		}
		if (commands_array[i][j] == '|' && commands_array[i][j + 1] == '|')
		{
			/* Split the line when '||' is found */
			temp = commands_array[i];
			commands_array[i][j] = '\0';
			commands_array[i] = str_duplicate(commands_array[i]);
			commands_array[i + 1] = str_duplicate(temp + j + 2);
			i++;
			operators_array[i] = '|';
			free(temp);
			j = 0;
		}
	}
	return (i);
}
