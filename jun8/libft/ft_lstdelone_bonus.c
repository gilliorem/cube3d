/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:03:32 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 21:00:53 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}

// void	del_content(void *content)
// {
// 	free(content);
// 	printf("Content freed\n");
// }

// int	main(void)
// {
// 	t_list *node = malloc(sizeof(t_list));
// 	if (!node)
// 		return (1);
// 	node->content = malloc(10);
// 	if (!node->content)
// 	{
// 		free(node);
// 		return (1);
// 	}
// 	node->next = NULL;

// 	ft_lstdelone(node, del_content);

// 	return (0);
// }

// Takes a pointer to a list node and a function pointer.
// Delete content of node using provided function and frees the node
// Check if node and the function pointer are not NULL before proceeding.
// Useful for freeing memory associated with a single node in a linked list.
// Used with other list manip functions to manage mem efficiently.
// Doesn't handle  next pointer of the node; frees the current node and content
