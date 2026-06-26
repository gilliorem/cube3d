/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:07:18 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/15 18:24:00 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while ((*nptr == 32) || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr++ == '-')
			sign *= -1;
	}
	while (*nptr >= 48 && *nptr <= 57)
		result = result * 10 + (*nptr++ - '0');
	return (result * sign);
}

// int main(void)
// {
//     const char *tests[] = {
//         "42",
//         "   -42",
//         "   +42abc",
//         "\t\n\v\f\r 1234",
//         "--42",
//         "",
//         "99999999999999999999",
//         "-99999999999999999999",
//         "+0",
//         "-0",
//         " \t\n\r\v\f+256",
//         "abc",
//         NULL
//     };

//     for (int i = 0; tests[i]; i++)
//     {
//         int std = atoi(tests[i]);
//         int custom = ft_atoi(tests[i]);
//         printf("Input: \"%s\"\n", tests[i]);
//         printf("Standard: %d\tCustom: %d\n\n", std, custom);
//     }

//     return 0;
// }
