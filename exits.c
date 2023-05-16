#include "shell.h"

/**
 **_strncpy - copying a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;/** char dest */

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];/** dest src */
		i++;
	}
	if (i < n)
	{
		j = i;/** j and i */
		while (j < n)
		{
			dest[j] = '\0';
			j++;/** j double */
		}
	}
	return (s);/** returning s */
}

/**
 **_strncat - concatenates the two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;/** char dest */

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;/** i double */
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];/** dest src */
		i++;
		j++;/** j double */
	}
	if (j < n)
		dest[i] = '\0';
	return (s);/** retyurning s */
}

/**
 **_strchr - locating a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);/** returning s */
	} while (*s++ != '\0');

	return (NULL);/** return NULL */
}
