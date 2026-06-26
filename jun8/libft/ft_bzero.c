/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:14:43 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/15 18:21:32 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*s1;

	i = 0;
	s1 = (char *)s;
	while (i < n)
		s1[i++] = 0;
}

// int	main(void)
// {
// 	char std[10] = "abcdefghi";
// 	char custom[10] = "abcdefghi";

// 	bzero(std + 2, 4);
// 	ft_bzero(custom + 2, 4);

// 	printf("Standard bzero: ");
// 	for (int i = 0; i < 10; i++)
// 		printf("%c ", std[i] ? std[i] : '.');
// 	printf("\n");

// 	printf("Custom ft_bzero: ");
// 	for (int i = 0; i < 10; i++)
// 		printf("%c ", custom[i] ? custom[i] : '.');
// 	printf("\n");

// 	return 0;
// }

// bzero() is deprecated in POSIX.1-2001 in favor of memset(s, 0, n)