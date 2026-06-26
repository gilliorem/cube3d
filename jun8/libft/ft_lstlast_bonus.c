/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:58:07 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 20:54:38 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include "libft.h"

// int	main(void)
// {
// 	t_list *node1 = ft_lstnew("One");
// 	t_list *node2 = ft_lstnew("Two");
// 	t_list *node3 = ft_lstnew("Three");

// 	node1->next = node2;
// 	node2->next = node3;

// 	t_list *last = ft_lstlast(node1);
// 	if (last)
// 		printf("Last node content: %s\n", (char *)last->content);

// 	// Optional: free nodes
// 	free(node1);
// 	free(node2);
// 	free(node3);

// 	return (0);
// }
// Takes pointer to head of LL & returns a pointer to the last node in the list.
// Iterates through list till find the last node (next pointer is NULL)
// Checks if the list is empty (NULL) and returns NULL in that case.
// Useful for operations that require access to the last node 
// such as adding a new node at the end of the list.
// Doesn't modify the list or nodes - only traverses the list to find last node
// Doesn't handle memory management for the nodes
