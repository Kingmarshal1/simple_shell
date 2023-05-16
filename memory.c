#include "shell.h"

/**
 * bfree - freeing a pointer and NULLs the address
 * @ptr: address of the pointer to free
 * Created by Chukwudike Igwe
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);/** free ptr */
		*ptr = NULL;
		return (1);/** returning 1 */
	}
	return (0);
}
