/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:54:52 by regillio          #+#    #+#             */
/*   Updated: 2025/05/23 15:55:03 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Adds the node 'new' at the beginning of the list.
 * lst : the adress of a pointer to the first node of the list.
 * new : the address of a pointer to the node to be added.
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = new;
	if (*lst)
	{
		new->next = *lst;
		*lst = new;
	}
	else
	{
		*lst = new;
		new->next = NULL;
	}
}
