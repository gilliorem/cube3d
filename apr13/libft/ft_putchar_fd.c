/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:33:23 by regillio          #+#    #+#             */
/*   Updated: 2025/05/16 19:33:36 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
