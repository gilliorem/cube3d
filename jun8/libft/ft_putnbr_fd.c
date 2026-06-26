/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:16:10 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/14 13:16:10 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned char	c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

/*int	main(void)
{
	int	fd;

	fd = 1;
	ft_putnbr_fd(12345, fd);
	write(fd, "\n", 1);
	ft_putnbr_fd(-12345, fd);
	write(fd, "\n", 1);
	ft_putnbr_fd(-2147483648, fd);
	write(fd, "\n", 1);
	ft_putnbr_fd(0, fd);
	write(fd, "\n", 1);
	return (0);
}*/

// Writes an integer to the specified file descriptor
// Takes an integer n and an integer fd as arguments