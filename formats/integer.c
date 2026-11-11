/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragliga <ragliga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 11:23:55 by ragliga           #+#    #+#             */
/*   Updated: 2026/11/09 13:30:42 by ragliga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	format_d_i(int nb)
{
	return (ft_putnbr(nb));
}

int	format_u(unsigned int nb)
{
	return (ft_putnbr_u(nb));
}
