/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:15:32 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/23 17:17:17 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		count;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = count_digits(n);
	ptr = (char *)malloc(sizeof(char) * (count + 1));
	if (!ptr)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		ptr[0] = '-';
	}
	ptr[count] = '\0';
	while (n > 0)
	{
		ptr[--count] = (n % 10) + '0';
		n /= 10;
	}
	return (ptr);
}

// int	main(void)
// {
// 	int test_vals[] = {0, 42, -42, 123456, -123456, -2147483648, 2147483647};
// 	for (int i = 0; i < 7; i++)
// 	{
// 		char *res = ft_itoa(test_vals[i]);
// 		printf("ft_itoa(%d) = %s\n", test_vals[i], res);
// 		free(res);
// 	}
// 	return 0;
// }
