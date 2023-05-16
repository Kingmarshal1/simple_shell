#include "shell.h"

/**
 * interactive - returning true if shell is interactive mode
 * @info: struct address
 * Created by Chukwudike Igwe
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);/** STDNIN FILE */
}

/**
 * is_delim - checking if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);/** returning 1 */
	return (0);
}

/**
 * _isalpha - checking for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);/** returning 1 */
	else
		return (0);
}

/**
 * _atoi - converts for a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;/** sign flag */
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;/** the sign */

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;/** the flag */
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;/** flagging 2 */
	}

	if (sign == -1)
		output = -result;
	else
		output = result;/** outputing the results */

	return (output);
}
