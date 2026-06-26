/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:15:14 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/25 15:33:42 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*int	main(void)
{
	int	c;

	c = 40;
	if (ft_isdigit(c))
		printf("Digit\n");
	else
		printf("Not a digit\n");
	return (0);
}*/
