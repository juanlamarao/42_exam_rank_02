/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:59:29 by juolivei          #+#    #+#             */
/*   Updated: 2020/03/18 21:20:21 by juanlamar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

typedef struct	s_flags
{
	int		i;
	int		len;
	int		width;
	int		have_precision;
	int		precision;
	int		negative;
	int		zero_count;
	int		output;
	va_list	arg;
}				t_flags;

static void	_ini_flags(t_flags *flags)
{
	flags->i = 0;
	flags->output = 0;
}

static void	_clear_flags(t_flags *flags)
{
	flags->len = 0;
	flags->width = 0;
	flags->have_precision = 0;
	flags->precision = 0;
	flags->negative = 0;
	flags->zero_count = 0;
}

static void	_putchar(char c)
{
	write(1, &c, 1);
}

static void	_putstr_len(const char *s, const int max_i)
{
	int i;

	i = 0;
	while (i < max_i && s[i])
	{
		_putchar(s[i]);
		i++;
	}
}

static int	_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	_longlen_base(long nbr, int base_len)
{
	int i;

	i = 1;
	while (nbr >= base_len)
	{
		nbr /= base_len;
		i++;
	}
	return (i);
}

static void	_putnbr_base(long nbr, int base_len, const char *base)
{
	if (nbr >= base_len)
	{
		_putnbr_base(nbr / base_len, base_len, base);
		_putnbr_base(nbr % base_len, base_len, base);
	}
	else
		_putchar(base[nbr]);
}

static void	_print_until(const char *s, char c, t_flags *flags)
{
	while (s[flags->i] && s[flags->i] != c)
	{
		_putchar(s[flags->i]);
		flags->i++;
		flags->output++;
	}
}

static int	_is_num(char c)
{
	return (c >= '0' && c <= '9');
}

static void	_discover_flags(const char *s, t_flags *flags)
{
	flags->i++;
	if (_is_num(s[flags->i]))
	{
		while (_is_num(s[flags->i]))
		{
			flags->width = (flags->width * 10) + (s[flags->i] - 48);
			flags->i++;
		}
	}
	if (s[flags->i] == '.')
	{
		flags->i++;
		flags->have_precision = 1;
		while (_is_num(s[flags->i]))
		{
			flags->precision = (flags->precision * 10) + (s[flags->i] - 48);
			flags->i++;
		}
	}
}

static void	_print_x_char(int len, char c, t_flags **flags)
{
	int	i;

	i = 0;
	while (i < len)
	{
		_putchar(c);
		(**flags).output++;
		i++;
	}
}

static void	_print_s(t_flags *flags)
{
	char	*s;

	flags->i++;
	s = va_arg(flags->arg, char *);
	if (!s)
		s = "(null)";
	flags->len = _strlen(s);
	if (flags->have_precision && flags->precision < flags->len)
		flags->len = flags->precision;
	_print_x_char(flags->width - flags->len, ' ', &flags);
	_putstr_len(s, flags->len);
	flags->output += flags->len;
}

static void	_print_d(t_flags *flags)
{
	long	nbr;

	flags->i++;
	nbr = va_arg(flags->arg, int);
	if (nbr < 0)
	{
		flags->negative = 1;
		nbr *= -1;
	}
	flags->len = _longlen_base(nbr, 10);
	if (nbr == 0 && flags->have_precision)
		flags->len = 0;
	if (flags->have_precision && flags->precision > flags->len)
		flags->zero_count = flags->precision - flags->len;
	if (flags->negative)
		flags->len++;
	_print_x_char(flags->width - (flags->zero_count + flags->len), ' ', &flags);
	if (flags->negative)
		_putchar('-');
	_print_x_char(flags->zero_count, '0', &flags);
	if (flags->have_precision && nbr == 0)
		return ;
	_putnbr_base(nbr, 10, "0123456789");
	flags->output += flags->len;
}

static void	_print_x(t_flags *flags)
{
	unsigned int	nbr;

	flags->i++;
	nbr = va_arg(flags->arg, unsigned int);
	flags->len = _longlen_base(nbr, 16);
	if (nbr == 0 && flags->have_precision)
		flags->len = 0;
	if (flags->have_precision && flags->precision > flags->len)
		flags->zero_count = flags->precision - flags->len;
	_print_x_char(flags->width - (flags->zero_count + flags->len), ' ', &flags);
	_print_x_char(flags->zero_count, '0', &flags);
	if (flags->have_precision && nbr == 0)
		return ;
	_putnbr_base(nbr, 16, "0123456789abcdef");
	flags->output += flags->len;
}

int			ft_printf(const char *fmt, ...)
{
	t_flags	flags;

	_ini_flags(&flags);
	va_start(flags.arg, fmt);
	while (fmt[flags.i])
	{
		_clear_flags(&flags);
		_print_until(fmt, '%', &flags);
		if (fmt[flags.i])
		{
			_discover_flags(fmt, &flags);
			if (fmt[flags.i] == 's')
				_print_s(&flags);
			else if (fmt[flags.i] == 'd')
				_print_d(&flags);
			else if (fmt[flags.i] == 'x')
				_print_x(&flags);
		}
	}
	return (flags.output);
}
