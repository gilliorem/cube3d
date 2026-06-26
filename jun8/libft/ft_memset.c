/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:15:54 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 20:28:10 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, unsigned int n)
{
	unsigned int	i;
	unsigned char	*s;
	unsigned char	c1;

	i = 0;
	s = (unsigned char *)str;
	c1 = (unsigned char)c;
	while (i++ < n)
		*s++ = c1;
	return (str);
}

/* #include <stdio.h>
#include <string.h>  // for memset, memcmp
#include <stdlib.h>  // for malloc, free

void	*ft_memset(void *str, int c, unsigned int n);

// Helper to run one test case
void	run_test(const char *test_name, unsigned char fill_char, unsigned int n)
{
	unsigned char buf_std[100] = {0};
	unsigned char buf_ft[100] = {0};

	memset(buf_std, fill_char, n);
	ft_memset(buf_ft, fill_char, n);

	if (memcmp(buf_std, buf_ft, n) == 0)
		printf("✅ %s passed\n", test_name);
	else
	{
		printf("❌ %s failed\n", test_name);
		printf("Expected: ");
		for (unsigned int i = 0; i < n; i++)
			printf("%02X ", buf_std[i]);
		printf("\nGot     : ");
		for (unsigned int i = 0; i < n; i++)
			printf("%02X ", buf_ft[i]);
		printf("\n");
	}
}

int main(void)
{
	run_test("Set 0 bytes", 0x41, 0);
	run_test("Set 1 byte", 0x42, 1);
	run_test("Set 5 bytes to 'A'", 'A', 5);
	run_test("Set 10 bytes to 0x00", 0x00, 10);
	run_test("Set 10 bytes to 0xFF", 0xFF, 10);
	run_test("Set full buffer to '*'", '*', 50);

	// Stress test
	run_test("Set 99 bytes to 0x7F", 0x7F, 99);

	return 0;
} */

// Fills first n bytes of the memory area pointed to by str with c.
// It returns a pointer to the memory area str.
// Useful for initializing or resetting memory areas.
// Doesn't check if memory area is NULL
// Doesn't check if n is zero
// Doesn't handle case where n exceeds the size of the allocated memory area
