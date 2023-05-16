#include "shell.h"

/**
 * _strcpy - coping a string
 * @dest: the destination
 * @src: the source
 * Created by Chukwudike Igwe
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);/** returning dest */
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;/** dest i */
	return (dest);
}

/**
 * _strdup - duplicating a string
 * @str: the string to duplicate
 * Created by Chukwudike Igwe
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;/** char ret */

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;/*length double */
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;/** ret lenght str */
	return (ret);
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 * Created by Chukwudike Igwe
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;/** returning */
	while (str[i] != '\0')
	{
		_putchar(str[i]);/** putchar str */
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Created by Chukwudike Igwe
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];/** static char buff */

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);/** write 1 buff */
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;/** buf double */
	return (1);
}
