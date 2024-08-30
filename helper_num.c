#include "shell.h"

/**
 * long_to_string - from int to str
 * @number: number
 * @string: saving buffer of the number as a string
 * @base: base to convert number
 *
 * Return: void
 */
void long_to_string(long number, char *string, int base)
{
	char letters[] = {"0123456789abcdef"};
	int i = 0;/*as the index*/
	int inNegative = 0;
	long c = number;

	if (c == 0)
		string[i++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (c)
	{
		if (c < 0)
			string[i++] = letters[-(c % base)];
		else
			string[i++] = letters[c % base];
		c /= base;
	}
	if (inNegative)
		string[i++] = '-';

	string[i] = '\0';
	str_reverse(string);
}


/**
 * _atoi - from string to an int
 * @s: ptr to str
 * Return: that int str ot 0
 */
int _atoi(char *s)
{
	unsigned int num = 0;
	int r = 1;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			r *= -1;
		if (*s == '+')
			r *= +1;
		s++;
	}

	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		num = (num * 10) + (*s - '0');
		s++;
	}
	return (num * r);
}

/**
 * count_characters - funct that counts coincidences char in str
 * @string: ptr
 * @character: str with chars
 * Return: int of str or 0
 */
int count_characters(char *string, char *character)
{
	int counter = 0;
	int s = 0;

	for (; string[s]; s++)
	{
		if (string[s] == character[0])
			counter++;
	}
	return (counter);
}
