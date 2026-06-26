/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:36:40 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/18 23:36:40 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

// int main(void)
// {
// 	    char *data = "Hello, Linked List!";
// 	    t_list *node = ft_lstnew(data);

// 	    if (!node)
// 	    {
// 	        printf("Failed to create node.\n");
// 	        return (1);
// 	    }

// 	    printf("Node content: %s\n", (char *)node->content);
// 	    printf("Node next: %p\n", (void *)node->next);

// 	    free(node);
// 	    return (0);
// }

// Creates a new node for a linked list
// It allocates memory for the node, sets its content to the provided value,
// and initializes the next pointer to NULL.
// Takes pointer to content as argument & returns a pointer to the created node.
// If memory allocation fails, it returns NULL.
// Used to create new nodes when building or manipulating linked lists.
// Doesn't check if the content is NULL; 
// it simply assigns the provided value to the content field of the new node.
