/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragliga <ragliga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 11:58:43 by ragliga           #+#    #+#             */
/*   Updated: 2026/11/10 10:08:30 by ragliga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putnbr(long n)
{
	int		i;
	int		j;
	char	c;

	if (n < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		j = ft_putnbr(-n);
		if (j == -1)
			return (-1);
		return (j + 1);
	}
	if (n >= 0 && n <= 9)
	{
		c = n + '0';
		return (write(1, &c, 1));
	}
	i = ft_putnbr(n / 10);
	if (i == -1)
		return (-1);
	j = ft_putnbr(n % 10);
	if (j == -1)
		return (-1);
	return (i + j);
}

int	ft_putnbr_u(unsigned int n)
{
	int		i;
	int		j;
	char	c;

	if (n >= 10)
	{
		i = ft_putnbr_u(n / 10);
		if (i == -1)
			return (-1);
		j = ft_putnbr_u(n % 10);
		if (j == -1)
			return (-1);
		return (i + j);
	}
	c = n + '0';
	return (write(1, &c, 1));
}
