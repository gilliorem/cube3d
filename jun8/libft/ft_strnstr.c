/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:17:12 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 16:38:15 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	const char	*b;
	const char	*l;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (*big && i < len)
	{
		b = big;
		l = little;
		j = i;
		while (*l && *b && *l++ == *b++ && j++ < len)
			if (!*l)
				return ((char *)big);
		i++;
		big++;
	}
	return (NULL);
}

/* #include <stdio.h>
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len);

int main(void)
{
	const char *big = "Hello, welcome to 42 SG!";
	const char *needle1 = "welcom";
	const char *needle2 = "42";
	const char *needle3 = "notfound";
	const char *needle4 = "";
	const char *needle5 = "SG";

 	// Test 1: Found within range
	printf("Test 1: ");
	char *res1 = ft_strnstr(big, needle1, 20);
	printf("%s\n", res1 ? res1 : "NULL");

	// Test 2: Found near the end
	printf("Test 2: ");
	char *res2 = ft_strnstr(big, needle2, 25);
	printf("%s\n", res2 ? res2 : "NULL");

	// Test 3: Not found
	printf("Test 3: ");
	char *res3 = ft_strnstr(big, needle3, 30);
	printf("%s\n", res3 ? res3 : "NULL");

	// Test 4: Empty needle
	printf("Test 4: ");
	char *res4 = ft_strnstr(big, needle4, 10);
	printf("%s\n", res4 ? res4 : "NULL");

	// Test 5: Found at the very end, check length edge case
	printf("Test 5: ");
	char *res5 = ft_strnstr(big, needle5, strlen(big));
	printf("%s\n", res5 ? res5 : "NULL");

} */

// Locates first occurrence of the string little in the string big
// Not more than len characters are searched in big
// Returns pointer to the beg of located substring, or NULL if not found
// If little is an empty string, pointer to big is returned
// Useful for searching for substrings within a specified length of larger str
// Doesn't modify the original strings; only searches for the substring.
// The function does not handle memory management for the strings
// Doesn't check if the strings are NULL
// Doesn't handle the case where the length len is zero; it simply returns NULL.
// Doesn't check for memory leaks; it is the caller's responsibility to free
// Doesn't check if substring is empty; simply returns the original string.
