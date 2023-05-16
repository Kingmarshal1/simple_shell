#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 * Created by Chukwudike Igwe
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;/** void info */
	if (!path || stat(path, &st))
		return (0);/** returning zero */

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);/** returning 0 */
}

/**
 * dup_chars - duplicating characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Created by Chukwudike Igwe
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];/** static char buffer */
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];/** buffer pathstr */
	buf[k] = 0;
	return (buf);/** returning buffer */
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;/** integer i curr pro */
	char *path;

	if (!pathstr)
		return (NULL);/** returning NULL */
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);/** return cmd */
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);/** pathstr cur */
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);/** strcat path cmd */
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;/** set to break */
			curr_pos = i;
		}
		i++;
	}
	return (NULL);/** returning NULL */
}
