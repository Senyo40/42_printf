/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragliga <ragliga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 11:11:13 by ragliga           #+#    #+#             */
/*   Updated: 2026/11/05 13:00:52 by ragliga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

int				ft_printf(const char *s, ...);

// Formats
int				format_c(char c);
int				format_s(char *s);
int				format_p(void *ptr);
int				format_d_i(int nb);
int				format_u(unsigned int nb);
int				format_x(unsigned int n);
int				format_bigx(unsigned int n);

// Libft
int				ft_putnbr(long n);
int				ft_putnbr_u(unsigned int n);

#endif