#include "shell.h"

/**
 * _myenv - printing the current environment
 * @info: Structure contains potential arguments used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);/** printing list str info */
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 * Created by Chukwudike Igwe
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;/** list the node */
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);/** start with node name */
		if (p && *p)
			return (p);
		node = node->next;/** node next */
	}
	return (NULL);
}

/**
 * _mysetenv - Begining  a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");/** incorrct numbers */
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);/** returning zero */
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");/** eputs too few arg */
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);/** unsetenv info argv */

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;/** size */

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);/** add node end environ */
	info->env = node;
	return (0);
}
