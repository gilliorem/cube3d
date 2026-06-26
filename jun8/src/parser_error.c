/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 07:27:55 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 07:27:57 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	parser_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int	parser_error_str(char *msg, char *value)
{
	ft_putstr_fd(msg, 2);
	if (value)
		ft_putstr_fd(value, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int	parser_error_char(char *msg, char value)
{
	ft_putstr_fd(msg, 2);
	ft_putchar_fd(value, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int	parser_error_count(char *msg, int n)
{
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('[', 2);
	ft_putnbr_fd(n, 2);
	ft_putstr_fd("]\n", 2);
	return (0);
}
