/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:15:47 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 20:35:53 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i++ < n)
		*d++ = *s++;
	return (dest);
}

/* #include <stdio.h>
#include <string.h>  // for memcpy, memcmp
#include <unistd.h>  // for write
#include <stdlib.h>  // for malloc, free

void	*ft_memcpy(void *dest, const void *src, size_t n);

// Helper to run a single test case
void run_test(const char *test_name, const void *src, size_t n)
{
	char dest1[100] = {0};
	char dest2[100] = {0};

	memcpy(dest1, src, n);
	ft_memcpy(dest2, src, n);

	if (memcmp(dest1, dest2, n) == 0)
	{
		printf("✅ %s passed\n", test_name);
	}
	else
	{
		printf("❌ %s failed\n", test_name);
		write(1, "Expected: ", 10); write(1, dest1, n); write(1, "\n", 1);
		write(1, "Got     : ", 10); write(1, dest2, n); write(1, "\n", 1);
	}
}

int main(void)
{
	// Basic tests
	run_test("Copy 'Hello'", "Hello", 5);
	run_test("Copy with null terminator", "42SG\0Cool", 8);
	run_test("Copy empty string", "", 0);
	run_test("Copy 1 byte", "A", 1);
	run_test("Copy 0 bytes", "Ignore me", 0);

	// Longer data
	char long_src[50] = "This is a much longer string for memcpy testing.";
	run_test("Copy long string", long_src, 45);

	// Copy with embedded nulls
	char bin_data[] = {0x00, 0x01, 0xFE, 0xFF, 0x00, 'X', 'Y'};
	run_test("Copy binary data with nulls", bin_data, sizeof(bin_data));

	// Overlapping memory (undefined behavior, but test anyway)
	char overlap[20] = "1234567890";
	memcpy(overlap + 2, overlap, 5); // expected to misbehave
	ft_memcpy(overlap + 2, overlap, 5); // same here
	printf("⚠️  Overlapping copy test done (undefined behavior)\n");

	return 0;
} */

// Copies n bytes from the source mem area src to the destination mem area dest
// Returns a pointer to the destination memory area dest.
// Does not check for overlapping memory areas; 
// if the source and destination overlap, the behavior is undefined.
// Doesn't handle memory allocation or deallocation; 
// assumes destination mem area is already allocated and large enough to hold.
// Doesn't check if the source or destination pointers are NULL; 
// simply copies the specified number of bytes.
