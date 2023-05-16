#include "shell.h"

/**
 * get_history_file - gets the usual history file
 * @info: parameter struct
 * Created by Chukwudike Igwe
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;/** character buf dir */

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);/** the return is NULL */
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);/** return buf */
}

/**
 * write_history - creating a file, or appends to an existing file
 * @info: the parameter struct
 * partnered project done by one
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;/** list node  = NULL */

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);/** free filename */
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);/** putsfd node str */
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);/** close fd */
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 * Created by Chukwudike Igwe
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;/** integer i, last linecount */
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);/** history file */

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);/** filename readonly */
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;/** fsize st size */
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);/** returning zero */
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);/** return free buf */
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;/** the last - 1+1 */
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;/** info history count - linecount */
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);/** return info histcount */
}

/**
 * build_history_list - adding entry to a hist. linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;/**node - info history */
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;/** info history */
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 * Partnered project
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;/** list node info history */
	int i = 0;

	while (node)
	{
		node->num = i++;/** node number */
		node = node->next;
	}
	return (info->histcount = i);
}
