#include "shell.h"

/**
 * _eputs - printing an input string
 * @str: the string to be printed
 * created by Chukwudike Igwe
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;/** return */
	while (str[i] != '\0')
	{
		_eputchar(str[i]);/** eputchar str */
		i++;
	}
}

/**
 * _eputchar - writing the character c to stderr
 * @c: The character to print
 * created by partners of the project
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];/** write buff size */

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);/** write 2 buff */
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;/** buffer */
	return (1);
}

/**
 * _putfd - writing the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];/** write buffer size */

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);/** write fd buf */
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);/** returning 1 */
}

/**
 * _putsfd - printing an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 * The work of two partners of this project
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);/** returning zero */
	while (*str)
	{
		i += _putfd(*str++, fd);/** put fd str */
	}
	return (i);
}
