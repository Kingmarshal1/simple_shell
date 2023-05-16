#include "shell.h"

/**
 * input_buf - buffering chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * created by Chukwudike Igwe
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;/** size of len p */

	if (!*len) /** if there is nothing in the buff, add it */
	{
		/** bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);/** getline buff */
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /** edit trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);/** remove comments buff */
			build_history_list(info, *buf, info->histcount++);
			/** if (_strchr(*buf, ';')) is that a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;/** info cmd buf */
			}
		}
	}
	return (r);
}

/**
 * get_input - getting a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /** the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;/** char buf p arg */

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i; /** getting a pointer for the return */

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;/** breaking points */
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;/** len 0 */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));/** returning strlen */
	}

	*buf_p = buf;
	return (r); /** returning r */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 * work by two
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);/** returning zero */
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);/** the return r */
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;/** size t */
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;/** lenght of s */
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);/** read buffer info */
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');/** strchr buffer */
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /** malloc failed */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);/** strncat new p buff */
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;/** new p */

	if (length)
		*length = s;
	*ptr = p;
	return (s);/** returning s */
}

/**
 * sigintHandler - blocking ctrl-C
 * @sig_num: the signal number
 * Created by Chukwudike Igwe
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");/** puts $ */
	_putchar(BUF_FLUSH);
}
