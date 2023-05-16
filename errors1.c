#include "shell.h"

/**
 * _erratoi - converting a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;/** unsigned lon int result */

	if (*s == '+')
		s++;  /** TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;/** results of 10 */
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);/** returning neg 1 */
		}
		else
			return (-1);
	}
	return (result);/** returning the results */
}

/**
 * print_error - printing an error message
 * @info: the parameter and return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");/** eputs */
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);/** eputs info argv */
	_eputs(": ");
	_eputs(estr);/** eputs estr */
}

/**
 * print_d - function printing a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;/** int count */
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;/** putchar */
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;/** counting double */
	}
	else
		_abs_ = input;
	current = _abs_;/** current abs */
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);/** putchar current */
			count++;
		}
		current %= i;/** current i */
	}
	__putchar('0' + current);
	count++;/** count double */

	return (count);
}

/**
 * convert_number - converter- function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * created by Chukwudike Igwe
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];/** static char buffer */
	char sign = 0;
	char *ptr;
	unsigned long n = num;/** unsigned long n */

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';/** signing */

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];/** ptr buffer */
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];/** ptr array base */
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;/** ptr sign */
	return (ptr);
}

/**
 * remove_comments - function replaces 1st instance of '#' with '\0'
 * @buf: address of the string to modify
 * Project done by two partners
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';/** buffer */
			break;
		}
}
