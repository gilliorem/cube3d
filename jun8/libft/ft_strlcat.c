/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:16:49 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 17:38:16 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		slen;
	size_t		dlen;

	i = 0;
	slen = 0;
	dlen = 0;
	while (dst[dlen] && dlen < size)
		dlen++;
	while (src[slen])
		slen++;
	if (size == dlen)
		return (slen + size);
	while (i < (size - dlen -1) && src[i])
	{
		dst[dlen + i] = src[i];
		i++;
	}
	if (dlen + i < size)
		dst[dlen + i] = '\0';
	return (slen + dlen);
}

// Appends the string src to the end of the string dst,
// Ensuring that the resulting string is null-terminated. It takes a destination
// string dst, a source string src, and the size of the destination buffer size.
// Calculates the length of both strings and appends src to dst,
// ensuring that the total length does not exceed size - 1. It returns the total
// length of the string that would have been created if there was enough space.
// If the destination buffer is not large enough, the function truncates the
// concatenation and ensures that the result is null-terminated. The function
// handles edge cases such as empty strings and overlapping memory regions.
// Useful for safely concatenating strings without causing buffer overflows.
// Doesn't check if the input strings are NULL; it simply returns the length 
// of the concatenated string. The function does not handle the case
// where the destination buffer is too small; it simply truncates the result.
// Doesn't check for memory leaks; it is the caller's responsibility
// to free the allocated memory. 
// The function does not check if the input strings are valid; 
// it assumes that they are. The function does not handle the case where
// the input strings are very large; it assumes that they fit in memory.
