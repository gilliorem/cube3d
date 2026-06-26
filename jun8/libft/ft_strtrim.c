/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:17:22 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 20:13:00 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		len;

	len = 0;
	while (ft_strchr(set, *s1) && *s1)
		s1++;
	if (!*s1)
		return (ft_strdup(""));
	while (s1[len])
		len++;
	while (ft_strchr(set, s1[len - 1]))
		len--;
	if (!len)
		return (ft_strdup(""));
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, len + 1);
	return (ptr);
}

/* #include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declare your ft_strtrim prototype
char *ft_strtrim(char const *s1, char const *set);

int main(void)
{
    char *result;

    // Test 1: Trimming common characters
    result = ft_strtrim("$$$Hello$World$$$", "$");
    printf("Test 1: '%s'\n", result);
    free(result);

    // Test 2: No characters to trim
    result = ft_strtrim("Hello", "$");
    printf("Test 2: '%s'\n", result);
    free(result);

    // Test 3: All characters trimmed
    result = ft_strtrim("$$$", "$");
    printf("Test 3: '%s'\n", result); // Should be empty string

    // Test 4: Empty string input
    result = ft_strtrim("", "$");
    printf("Test 4: '%s'\n", result);

    // Test 5: Empty set
    result = ft_strtrim("Hello", "");
    printf("Test 5: '%s'\n", result);
    free(result);

    // Test 6: Trimming whitespace
    result = ft_strtrim("   \t\nHello\n\t   ", " \n\t");
    printf("Test 6: '%s'\n", result);
    free(result);

    return 0;
}
  */

// Trims characters specified in the set from both ends of the string s1.
// Returns a new string with the trimmed content.
// If i/p string is empty or all characters are trimmed, return empty string
// Allocates memory for the new string, caller is responsible for freeing it
// Doesn't modify the original string
// Doesn't check for memory leaks
// Doesn't check if i/p strings are NULL; assumes caller will provide valid i/p
// Doesn't handle case if input strings are very large; assumes they fit in mem
// Doesn't check for mem allocation errors; assumes caller will handle errors
// Doesn't check if i/p strings are valid; it assumes that they are
// Doesn't check if i/p strings are NULL; it simply returns an empty string.
