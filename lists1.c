#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 * Created by Chukwudike Igwe
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;/** size of t */

	while (h)
	{
		h = h->next;/** next h */
		i++;
	}
	return (i);/** returning i */
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 * Created by Chukwudike Igwe
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;/** list node head */
	size_t i = list_len(head), j;
	char **strs;/** char strs */
	char *str;

	if (!head || !i)
		return (NULL);/** returning NULL */
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);/** returning NULL */
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);/** malloc strlen */
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);/** free strs */
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);/** strcpy node str */
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);/** returning strs */
}


/**
 * print_list - printing all elements of a list t linked list
 * @h: pointer to first node
 * created by bpartners of this project
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;/** size of t */

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');/** putchar */
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");/** puts str */
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);/** returning i */
}

/**
 * node_starts_with - returning node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;/** char NULL */

	while (node)
	{
		p = starts_with(node->str, prefix);/** starts with node prefix */
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);/** returning NULL */
}

/**
 * get_node_index - gettting the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * job done by two partners
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;/** size of t */

	while (head)
	{
		if (head == node)
			return (i);/** returning i */
		head = head->next;
		i++;
	}
	return (-1);/** returning neg 1 */
}
