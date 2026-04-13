/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:46:43 by regillio          #+#    #+#             */
/*   Updated: 2026/02/08 10:42:10 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <fcntl.h> // open and close
#include <sys/stat.h> // S_IRWXU  
*/
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
	ft_putchar_fd('\n', fd);
}

