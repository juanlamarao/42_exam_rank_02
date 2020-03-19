/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:06:15 by juolivei          #+#    #+#             */
/*   Updated: 2020/03/18 21:09:39 by juanlamar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	_find_char(const char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}

static char	*_calloc(int len, int count)
{
	char	*p;
	int		size;
	int		i;

	i = 0;
	size = len * count;
	if (!(p = malloc(size)))
		return (NULL);
	while (i < size)
	{
		p[i] = '\0';
		i++;
	}
	return (p);
}

static char	*_stradd_char(char *str, char c)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	len = _strlen(str);
	new = (char *)_calloc(len + 2, sizeof(char));
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	if (str)
		free(str);
	return (new);
}

static char	*_substr(const char *str, int begin, int len)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)_calloc(len + 1, sizeof(char));
	while (str[begin] && i < len)
		new[i++] = str[begin++];
	return (new);
}

int			get_next_line(char **line)
{
	static char *s;
	char buffer[1];
	char *tmp;
	int	pos;

	if (!line) || (!(s) && !(s = _calloc(1, sizeof(char))))
		return (-1);
	while (read(0, buffer, 1) > 0)
	{
		s = _stradd_char(s, buffer[0]);
		if (buffer[0] == '\n')
			break ;
	}
	if ((pos = _find_char(s, '\n')) >= 0)
	{
		*line = _substr(s, 0, pos);
		tmp = s;
		s = _substr(s, pos + 1, _find_char(s, '\0'));
		free(tmp);
		return (1);
	}
	*line = _substr(s, 0, '\0');
	free(s);
	return (0);
}
