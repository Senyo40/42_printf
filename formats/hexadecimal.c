/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexadecimal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragliga <ragliga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 11:56:13 by ragliga           #+#    #+#             */
/*   Updated: 2026/11/10 10:07:39 by ragliga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	print_uhex(unsigned long long n)
{
	int		i;
	int		j;
	char	*base;

	base = "0123456789abcdef";
	if (n >= 16)
	{
		i = print_uhex(n / 16);
		if (i == -1)
			return (-1);
		j = print_uhex(n % 16);
		if (j == -1)
			return (-1);
		return (i + j);
	}
	return (write(1, &base[n], 1));
}

int	format_p(void *ptr)
{
	int					i;
	unsigned long long	ptr_2;

	if (!ptr)
	{
		return (write(1, "(nil)", 5));
	}
	ptr_2 = (unsigned long long)ptr;
	if (write(1, "0x", 2) == -1)
		return (-1);
	i = print_uhex(ptr_2);
	if (i == -1)
		return (-1);
	return (i + 2);
}

int	format_x(unsigned int n)
{
	int			i;
	int			j;
	char		*base;

	base = "0123456789abcdef";
	if (n >= 16)
	{
		i = format_x(n / 16);
		if (i == -1)
			return (-1);
		j = format_x(n % 16);
		if (j == -1)
			return (-1);
		return (i + j);
	}
	return (write(1, &base[n], 1));
}

int	format_bigx(unsigned int n)
{
	int			i;
	int			j;
	char		*base;

	base = "0123456789ABCDEF";
	if (n >= 16)
	{
		i = format_bigx(n / 16);
		if (i == -1)
			return (-1);
		j = format_bigx(n % 16);
		if (j == -1)
			return (-1);
		return (i + j);
	}
	return (write(1, &base[n], 1));
}
