/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:03:22 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 20:58:32 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// // Simple print function to use with ft_lstiter
// void	print_with_prefix(void *content)
// {
// 	printf("Node content: %s\n", (char *)content);
// }

// int	main(void)
// {
// 	t_list	*node1 = ft_lstnew("Alpha");
// 	t_list	*node2 = ft_lstnew("Beta");
// 	t_list	*node3 = ft_lstnew("Gamma");

// 	// Connect nodes manually or use ft_lstadd_back
// 	node1->next = node2;
// 	node2->next = node3;

// 	printf("Applying ft_lstiter:\n");
// 	ft_lstiter(node1, print_with_prefix);

// 	// Optional: free memory (if ft_lstclear is available)
// 	free(node1);
// 	free(node2);
// 	free(node3);

// 	return (0);
// }

// Takes pointer to the head of a linked list and a function pointer.
// Applies the function to each element in the list.
// Function iterates through list, calling function on each node's content
// Doesn't return anything and modifies the list in place.
// Check if list and the function pointer are not NULL before proceeding.
// Use to apply spec operation to each element in the list w/o modi list str
// Use for operations like printing or transforming the content of each node
// Doesn't handle memory management for the nodes
// Allows for flexible and reusable operations on the list elements.
