/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragliga <ragliga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 10:05:14 by ragliga           #+#    #+#             */
/*   Updated: 2026/11/10 10:05:17 by ragliga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	valid_format(char c)
{
	char	*formats;

	formats = "cspdiuxX%";
	while (*formats)
	{
		if (c == *formats)
			return (1);
		formats++;
	}
	return (0);
}

static int	print_next(char c, va_list *args)
{
	if (c == 'c')
		return (format_c(va_arg(*args, int)));
	if (c == 's')
		return (format_s(va_arg(*args, char *)));
	if (c == 'p')
		return (format_p(va_arg(*args, void *)));
	if (c == 'd' || c == 'i')
		return (format_d_i(va_arg(*args, int)));
	if (c == 'u')
		return (format_u(va_arg(*args, unsigned int)));
	if (c == 'x')
		return (format_x(va_arg(*args, unsigned int)));
	if (c == 'X')
		return (format_bigx(va_arg(*args, unsigned int)));
	if (c == '%')
		return (write(1, "%", 1));
	return (0);
}

static int	print_one(const char **s, va_list *args)
{
	int	i;

	if (**s == '%' && valid_format(*(*s + 1)))
	{
		i = print_next(*(*s + 1), args);
		*s += 2;
		return (i);
	}
	i = write(1, *s, 1);
	(*s)++;
	return (i);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		j;
	va_list	args;

	if (s == NULL)
		return (-1);
	i = 0;
	va_start(args, s);
	while (*s)
	{
		j = print_one(&s, &args);
		if (j == -1)
		{
			va_end(args);
			return (-1);
		}
		i += j;
	}
	va_end(args);
	return (i);
}
