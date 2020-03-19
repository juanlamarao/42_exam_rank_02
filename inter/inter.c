/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:34:21 by juolivei          #+#    #+#             */
/*   Updated: 2020/03/18 21:03:22 by juanlamar        ###   ########.fr       */
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
	while (s[i] && i < max_i)
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	_inter(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (!_contain_until(s1[i], s1, i) && _contain_until(s1[i], s2, 10000))
			_putchar(s1[i]);
		i++;
	}
}

int			main(int argc, char *argv[])
{
	if (argc == 3)
		_inter(argv[1], argv[2]);
	_putchar('\n');
	return (0);
}
