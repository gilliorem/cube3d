/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:17:26 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 16:22:23 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	char			*ptr1;
	size_t			j;
	size_t			s_len;

	if (!s)
		return (NULL);
	s_len = 0;
	while (s[s_len])
		s_len++;
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ptr1 = ptr;
	s += start;
	j = 0;
	while (j++ < len && *s)
		*ptr1++ = *s++;
	*ptr1 = '\0';
	return (ptr);
}

/* int	main(void)
{
	char *result;

	result = ft_substr("libft", 0, 3);
	printf("ft_substr(\"libft\", 0, 3) = \"%s\"\n", result);
	free(result);

	result = ft_substr("libft", 2, 10);
	printf("ft_substr(\"libft\", 2, 10) = \"%s\"\n", result);
	free(result);

	result = ft_substr("libft", 10, 3);
	printf("ft_substr(\"libft\", 10, 3) = \"%s\"\n", result);
	free(result);

	result = ft_substr("", 0, 3);
	printf("ft_substr(\"\", 0, 3) = \"%s\"\n", result);
	free(result);

	result = ft_substr("42", 1, 1);
	printf("ft_substr(\"42\", 1, 1) = \"%s\"\n", result);
	free(result);

	result = ft_substr(NULL, 0, 1);
	printf("ft_substr(NULL, 0, 1) = %s\n", result ? result : "NULL");

	return 0;
}
 */
// Allocates memory for a new str & copies a substr from the original string s.
// Substring starts at the index specified by start and has a max length of len.
// If start is greater than the length of s, an empty string is returned.
// If len is greater than remaining length of s, substr will be truncated to fit
// Returns a pointer to the newly allocated substring
// The caller is responsible for freeing the allocated memory
// The function doesn't check for memory leaks; that is caller's responsibility
// The function doesn't check if the input string s is NULL;
// assumes caller will provide a valid string
// Doesn't check for memory allocation errors; assumes caller will handle errors
// Doesn't check if the input string is valid; it assumes that it is.
// Doesn't check if input string is very large; assumes it fits in memory.
// Doesn't handle case where input string is empty; returns empty string.