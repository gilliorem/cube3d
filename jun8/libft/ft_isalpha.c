/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:15:06 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/23 17:07:38 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// int main(void)
// {
// 	for (int i = -1; i <= 130; i++)
// 	{
// 		int std = isalpha(i);
// 		int custom = ft_isalpha(i);
// 		if ((std != 0) != (custom != 0))
// 			printf("Mismatch %d: isalpha=%d, ft_isalpha=%d\n", i, std, custom);
// 	}
// 	printf("Test completed.\n");
// 	return 0;
// }

// Standard isalpha() is defined for values 0–255 and EOF (-1). 
// If c is outside this range (e.g. negative values other than EOF), 
// the behavior of the standard isalpha() is undefined. 