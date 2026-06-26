/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:17:18 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 20:31:50 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	count;

	count = 0;
	while (s[count])
		count++;
	if (!c)
	{
		if (!*s)
			return ((char *)s);
		else
			return ((char *)(s + count));
	}
	while (count > 0)
	{
		if (s[count - 1] == (unsigned char)c)
			return ((char *)(&s[count - 1]));
		count--;
	}
	return (NULL);
}

// Locates the last occurrence of a character in a string
// Returns a pointer to the last occurrence of c in s
// If c is not found, returns NULL. 
// If c is '\0', returns a pointer to the null terminator in s
// Returns NULL if c is not found in s
// Doesn't modify the original string
// Doesn't check if s is NULL; assumes caller will provide a valid string.
