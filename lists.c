#include "shell.h"

/**
 * add_node - adding a node to the starting of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 * created by Chukwudike Igwe
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);/** returning NULL */
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));/** memset void new head */
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);/** new head str */
		if (!new_head->str)
		{
			free(new_head);/** free new head */
			return (NULL);
		}
	}
	new_head->next = *head;/** new head next */
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adding a node to the end of the listing
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 * craeted by chukwudike Igwe
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;/** list new node */

	if (!head)
		return (NULL);/** returning NULL */

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));/** memset new node */
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);/** free new node */
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;/** node next */
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);/** return new node */
}

/**
 * print_list_str - printing only the str element of a list linked list
 * @h: pointer to first node
 * partnered project
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;/** size of t */

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");/** puts in new line */
		h = h->next;
		i++;
	}
	return (i);/** returning i */
}

/**
 * delete_node_at_index - deleting node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;/** unsigned integer */

	if (!head || !*head)
		return (0);/** returning zero */

	if (!index)
	{
		node = *head;
		*head = (*head)->next;/** head next */
		free(node->str);
		free(node);
		return (1);/** returning 1 */
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;/** prev node next */
			free(node->str);
			free(node);
			return (1);/** returning 1 */
		}
		i++;
		prev_node = node;
		node = node->next;/** node next */
	}
	return (0);
}

/**
 * free_list - freeing all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;/** list node head */

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;/** head ptr */
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);/** free node str */
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;/** head ptr NULL */
}
