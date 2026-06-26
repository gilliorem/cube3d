/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:16:29 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 20:20:48 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

/* #include <stdio.h>
#include <string.h>  // for strchr

char	*ft_strchr(const char *s, int c);

void	run_test(const char *test_name, const char *input, int ch)
{
	const char *expected = strchr(input, ch);
	char *actual = ft_strchr(input, ch);

	if (expected == actual)
	{
		printf("✅ %s passed\n", test_name);
	}
	else
	{
		printf("❌ %s failed\n", test_name);
		printf("Expected: %s\n", expected ? expected : "NULL");
		printf("Got     : %s\n", actual ? actual : "NULL");
	}
} */

/* int main(void)
{
	run_test("Find 'e' in string", "Hello, 42 Singapore!", 'e');
	run_test("Find 'H' at start", "Hello", 'H');
	run_test("Find ',' in middle", "Hi, friend", ',');
	run_test("Find null terminator", "Test", '\0');
	run_test("Find char not present", "ABCDE", 'z');
	run_test("Find first 'o' in 'tool'", "tool", 'o');
	run_test("Find last char '!' in string", "Hey!", '!');
	run_test("Find digit", "123456789", '5');
	run_test("Empty string with '\\0'", "", '\0');
	run_test("Empty string with non-null", "", 'x');

	return 0;
} */

// Locates the first occurrence of the character c in the string s.
// Returns pointer to the located char, or NULL if the char isn't found
// Doesn't modify the string; it only searches for the character
// Doesn't check if the string is NULL; it simply searches the string
// if char is not found; it returns NULL