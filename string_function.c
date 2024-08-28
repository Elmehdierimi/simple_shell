#include "shell.h"

/**
 * str_len - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int str_len(char *str)
{
	int len = 0;

	if (!str)
		return (0);

	while (*str++)
		len++;
	return (len);
}

/**
 * str_cmp - compares two strings lexicographically.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negativ if str1 < str2, positiv if str1 > str2, zero if str1 == str2
 */
int str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * begins_with - checks if a string starts with a given substring
 * @main_str: string to search
 * @sub_str: the substring to find
 *
 * Return: pointer to next char in main_str or NULL
 */
char *begins_with(const char *main_str, const char *sub_str)
{
	while (*sub_str)
		if (*sub_str++ != *main_str++)
			return (NULL);
	return ((char *)main_str);
}

/**
 * str_concat - concatenates two strings
 * @dest_str: the destination buffer
 * @src_str: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *str_concat(char *dest_str, char *src_str)
{
	char *ret_val = dest_str;

	while (*dest_str)
		dest_str++;
	while (*src_str)
		*dest_str++ = *src_str++;
	*dest_str = *src_str;
	return (ret_val);
}
