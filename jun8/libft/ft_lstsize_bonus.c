/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:41:03 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 20:41:03 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

/* // Helper function to create a new list node
t_list	*ft_lstnew(void *content)
{
	t_list	*node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

int	main(void)
{
	// Create three nodes
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");

	// Link the nodes
	node1->next = node2;
	node2->next = node3;

	// Call ft_lstsize and print result
	printf("List size: %d\n", ft_lstsize(node1));

	// Free the list
	free(node1);
	free(node2);
	free(node3);

	return (0);
}
 */

// Takes pointer to the head of a LL and returns # of elements in the list.
// Iterate through the list, count each node until it reaches the end (NULL)
// Check if the list is empty (NULL) and return 0 in that case.
// Doesn't modify the list or its nodes; 
// only traverses the list to count the nodes.
// Doesn't check if the list is empty; it simply returns 0 in that case.
