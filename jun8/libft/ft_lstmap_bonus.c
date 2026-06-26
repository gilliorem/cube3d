/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:03:05 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 20:52:23 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

// void	*to_uppercase(void *str)
// {
// 	char	*s = strdup((char *)str);
// 	for (int i = 0; s[i]; i++)
// 		if (s[i] >= 'a' && s[i] <= 'z')
// 			s[i] -= 32;
// 	return ((void *)s);
// }

// void	delete_content(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_list	*lst1 = ft_lstnew(strdup("apple"));
// 	t_list	*lst2 = ft_lstnew(strdup("banana"));
// 	t_list	*lst3 = ft_lstnew(strdup("cherry"));

// 	lst1->next = lst2;
// 	lst2->next = lst3;

// 	t_list *mapped = ft_lstmap(lst1, to_uppercase, delete_content);

// 	for (t_list *curr = mapped; curr; curr = curr->next)
// 		printf("%s\n", (char *)curr->content);

// 	ft_lstclear(&lst1, delete_content);
// 	ft_lstclear(&mapped, delete_content);
// 	return (0);
// }

// Takes a pointer to the head of LL, a fn pointer f, and a fn pointer del
// Applies fn f to each element in the list, creating a new list with results
// If allocation for a new node fails, clears new list using the del function
// Checks if list and the function pointers are not NULL before proceeding
// Useful for transforming content of each node while preserving original list
// Typically used for operations like mapping filtering or transforming content
// Doesn't modify original list; creates new list with transformed content
// Doesn't handle memory management for the nodes;
// Doesn't handle next pointer of the node; only frees current node and content
