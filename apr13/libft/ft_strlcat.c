/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <regillio@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:54:09 by regillio          #+#    #+#             */
/*   Updated: 2025/05/07 20:55:23 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static size_t	ft_strnlen(const char *s, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && (s[i] != '\0'))
		i++;
	return (i);
}
/*
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	dest_len = ft_strnlen(dest, size);
	i = dest_len;
	if (dest_len == size)
		return (size + src_len);
	while (i < size - 1 && *src != '\0')
	{
		dest[i] = *src;
		i++;
		src++;
	}
	dest[i] = '\0';
	return (dest_len + src_len);
}
*/
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	printf("size:%ld\n", size);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	dest_len = ft_strnlen(dest, size);
	i = dest_len;
	if (dest_len == size)
		return (size + src_len);
	while (i < size - 1 && *src != '\0')
	{
		dest[i] = *src;
		i++;
		src++;
	}
	dest[i] = '\0';
	printf("return: dest+len:%ld+%ld=%ld\n", dest_len, src_len, dest_len + src_len);
	return (dest_len + src_len);
}

