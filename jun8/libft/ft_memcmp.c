/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:15:43 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 20:38:23 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	i = -1;
	if (!n)
		return (0);
	while (++i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
	}
	return (0);
}

// Compares two blocks of memory byte by byte.
// Takes two pointers to the memory blocks and the number of bytes to compare.
// Returns an integer less than, equal to, or greater than zero,
// depending on whether the first block is less than, equal to, 
// or greater than the second block.
// Useful for comparing binary data or strings.
// Doesn't modify the memory blocks; only compares the speci number of bytes.
// Doesn't handle memory management for the memory blocks
// Doesn't check if memory blocks are NULL;
