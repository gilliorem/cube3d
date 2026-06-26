/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:10:50 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/23 17:19:13 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

// int	main(void)
// {
// 	t_list	*head = NULL;
// 	t_list	*node1 = ft_lstnew("first");
// 	t_list	*node2 = ft_lstnew("second");
// 	t_list	*node3 = ft_lstnew("third");

// 	ft_lstadd_back(&head, node1);
// 	ft_lstadd_back(&head, node2);
// 	ft_lstadd_back(&head, node3);

// 	t_list *tmp = head;
// 	while (tmp)
// 	{
// 		printf("%s\n", (char *)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }
// Create a linked list with three nodes and prints their contents.
// Adds new nodes to the end of the list.
// function does not return anything,- modifies the list in place.
// function takes a pointer to the head of the list and a new node to be added
// traverses list to find last node and sets its next pointer to the new node.
// If list is empty, it sets the head pointer to the new node.
// handle the case where the list is empty by checking if *lst is NULL
// Also check if the new node is NULL before attempting to add it to the list