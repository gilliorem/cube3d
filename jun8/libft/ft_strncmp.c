/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:17:08 by mohikhan          #+#    #+#             */
/*   Updated: 2025/08/16 12:02:26 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (*s1 && *s2 && i < n && *s1 == *s2)
	{
		s1++;
		s2++;
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

// Declare your ft_strncmp prototype
// int	ft_strncmp(const char *s1, const char *s2, size_t n);

// void test_case(const char *s1, const char *s2, size_t n)
// {
//     int std_result = strncmp(s1, s2, n);
//     int ft_result = ft_strncmp(s1, s2, n);

//     printf("Comparing \"%s\" and \"%s\" with n = %zu\n", s1, s2, n);
//     printf("strncmp   : %d\n", std_result);
//     printf("ft_strncmp: %d\n", ft_result);
//     if ((std_result == 0 && ft_result == 0) || 
//         (std_result < 0 && ft_result < 0) || 
//         (std_result > 0 && ft_result > 0))
//         printf("✅ PASS\n\n");
//     else
//         printf("❌ FAIL\n\n");
// }

// int main(void)
// {
// 	printf("%d\n", ft_strncmp("", "a",1));
// 	printf("%d\n", strncmp("", "a",1));
//     return (0);
// }
