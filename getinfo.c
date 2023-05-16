#include "shell.h"

/**
 * clear_info - initializing info_t struct
 * @info: struct address
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;/** info argv NULL */
	info->path = NULL;
	info->argc = 0;/** info argc */
}

/**
 * set_info - initializing info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];/** info file name */
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);/** malloc size */
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;/** info argc NULL */
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;/** info argc i */

		replace_alias(info);
		replace_vars(info);/** replace vars info */
	}
}

/**
 * free_info - freeing info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;/** info argv NULL */
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);/** free info arg */
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));/** free list history */
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);/** ffree info environ */
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);/** close info readfd */
		_putchar(BUF_FLUSH);
	}
}
