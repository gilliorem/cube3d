/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:15:02 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/15 18:30:18 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
		return (c);
	else
		return (0);
}

/*int	main(void)
{
	int	c;

	c = 'A';
	if (ft_isalnum(c))
		printf("It is alnum\n");
	else
		printf("It's not an alnum\n");
	return (0);
}*/
