/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:51:14 by juolivei          #+#    #+#             */
/*   Updated: 2020/03/18 21:02:15 by juanlamar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	_putchar(char c)
{
	write(1, &c, 1);
}

static int	_contain_until(char c, const char *s, int max_i)
{
	int	i;

	i = 0;
	while (i < max_i && s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	_union(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while(s1[i])
	{
		if (!_contain_until(s1[i], s1, i))
			_putchar(s1[i]);
		i++;
	}
	i = 0;
	while(s2[i])
	{
		if (!_contain_until(s2[i], s2, i) && !_contain_until(s2[i], s1, 10000))
			_putchar(s2[i]);
		i++;
	}
}

int			main(int argc, char *argv[])
{
	if (argc == 3)
		_union(argv[1], argv[2]);
	_putchar('\n');
	return (0);
}
