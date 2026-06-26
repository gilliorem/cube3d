/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:16:55 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 20:15:22 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		i;
	const char	*s;
	int			count;

	i = 0;
	count = 0;
	s = src;
	while (*s++)
		count++;
	if (size > 0)
	{
		while (i++ < (size - 1) && *src)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (count);
}

// Copies a string from src to dst, ensuring that the destination
// buffer is null-terminated and does not exceed the specified size.
// Returns total length of the string it tried to create, which is srclen
// Useful for safely copying strings while preventing buffer overflows

// Doesn't check for NULL pointers, assumes that the input strings are valid.
// Doesn't handle memory management for the destination buffer; it assumes
// that the caller will manage the memory.
// Doesn't check if the destination buffer is large enough; it simply truncates
// the string if necessary.
// Doesn't handle the case where source string is empty; it simply copies it.
// Doesn't check if source string is NULL; simply returns the seclen 0
// Doesn't handle case where destination buffer is NULL; simply returns srclen
// Doesn't handle case where input strings are very large; assumes they fit
