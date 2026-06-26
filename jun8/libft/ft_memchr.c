/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:15:39 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 20:40:40 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s1;
	size_t			i;

	s1 = (unsigned char *)s;
	i = 0;
	while (i++ < n)
	{
		if (*s1 == (unsigned char)c)
			return ((void *)s1);
		s1++;
	}
	return (NULL);
}

/*int	main(void)
{
	char	*str;
	char	*a;

	str = "Welcome to 42 Singapore";
	a = ft_memchr(str, 'W', 15);
	write (1, a, ft_strlen(a));

}*/

// Searches for the first occurrence of a character in a block of memory.
// takes pointer to mem block, char to search, & number of bytes to search.
// Returns pointer to first occurrence of the character in the memory block, 
// or NULL if not found.
// Useful for searching for a specific character in a binary or text data.
// Doesn't modify the memory block; it only searches for the character.
// Doesn't handle memory management for the memory block;
// Doesn't check if the memory block is NULL; 
