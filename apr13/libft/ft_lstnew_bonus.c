/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:00:14 by regillio          #+#    #+#             */
/*   Updated: 2025/05/23 16:01:10 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* allocates memory and returns a new node 
 * with initialized parameter 'content:content' next:NULL
 */

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
