/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:16:43 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 20:19:46 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*ptr;
	char	*ptr1;
	size_t	length;

	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(sizeof(char) * (length + 1));
	if (!ptr)
		return (NULL);
	ptr1 = ptr;
	while (*s1)
		*ptr1++ = *s1++;
	while (*s2)
		*ptr1++ = *s2++;
	*ptr1 = '\0';
	return (ptr);
}

// Concatenates two strings s1 and s2 into a new dynamically allocated string.
// It returns a pointer to the new string, or NULL if the allocation fails.
// First check if either s1 or s2 is NULL, and if so, it returns NULL.
// Calculates the length of the new string, allocates memory, 
// and copies the contents of s1 and s2 into it.
// Finally, it adds a null terminator to the end of the new string 
// and returns the pointer to it.
// Doesn't handle the case where s1/s2 is empty; simply concatenates them.
// Doesn't check for memory leaks;
// Doesn't check if the input strings are valid; it assumes that they are.
// Doesn't handle where i/p strings are large; assumes they fit in memory.
