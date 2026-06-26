/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:14:54 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/23 17:01:59 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*p;
	size_t	i;

	if (!nmemb || !size)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	p = malloc(nmemb * size);
	if (!p)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
		p[i++] = 0;
	return (p);
}

/*int	main(void)
{
	int	*ptr;
	int	i;

	i = 0;
	ptr = (int *)ft_calloc(5, sizeof(int));
	if (ptr == NULL)
		exit (1);
	while (i < 5)
	{
		printf("%p\n", ptr++);
		i++;
	}
	return (0);
}*/

// Overflow protection: check for nmemb > SIZE_MAX / size
// If nmemb * size exceeds SIZE_MAX, return NULL to prevent overflow.
// Important to avoid undefined behavior when allocating memory
// allocates memory for an array of nmemb elements, each of size size.
// initialize allocated memory to 0 and return a ptr to allocated memory
// If the allocation fails, return NULL.