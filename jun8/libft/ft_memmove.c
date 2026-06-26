/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:28:26 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 20:31:16 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*(--d) = *(--s);
	}
	return (dest);
}

/* #include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len);

void print_test(const char *label, char *str)
{
	printf("%s: \"%s\"\n", label, str);
} */

/* int	main(void)
{
	char a1[20] = "1234567890";
	char a2[20] = "1234567890";

	printf("Non-overlapping copy:\n");
	ft_memmove(a1 + 5, a1, 5);
	memmove(a2 + 5, a2, 5);
	print_test("ft_memmove", a1);
	print_test("memmove   ", a2);

	char b1[20] = "abcdef";
	char b2[20] = "abcdef";

	printf("\nOverlapping forward copy (src < dst):\n");
	ft_memmove(b1 + 2, b1, 4);
	memmove(b2 + 2, b2, 4);
	print_test("ft_memmove", b1);
	print_test("memmove   ", b2);

	char c1[20] = "abcdef";
	char c2[20] = "abcdef";

	printf("\nOverlapping backward copy (dst < src):\n");
	ft_memmove(c1, c1 + 2, 4);
	memmove(c2, c2 + 2, 4);
	print_test("ft_memmove", c1);
	print_test("memmove   ", c2);

	char *null_result = ft_memmove(NULL, NULL, 5);
	printf("\nNULL case (should be NULL): %p\n", null_result);

	return 0;
} */

// Copies n bytes from the source area src to the destination memory area dest.
// Handles overlapping memory areas correctly;
// by checking the relative positions of src and dest.
// If the destination is before the source, copy from the beginning
// If the destination is after the source, copy from the end
// The function returns a pointer to the destination memory area dest.
// Useful for safely copying memory when the source and destination may overlap.
// Doesn't check for NULL pointers; if src or dest is NULL, is undefined.
// If n is zero; it simply returns dest without performing any copy.