/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:16:33 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 17:44:29 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char		*ptr;
	char		*ptr1;
	const char	*s1;

	s1 = s;
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s)+1));
	if (!ptr)
		return (NULL);
	ptr1 = ptr;
	while (*s1)
		*ptr1++ = *s1++;
	*ptr1 = '\0';
	return (ptr);
}

/*int	main(void)
{
	char	*str;

	str = "Welcome to 42 Singapore";
	printf ("%s", ft_strdup(str));
	return (0);
}*/

// Duplicates a string by allocating memory for a new string and copying 
// contents of the original string into it.
// Takes a pointer to orig str as argument & returns pointer to the newly 
// allocated string. If the allocation fails, it returns NULL. 
// Finally, it adds a null terminator to the end of the new string. 
// Useful for creating a copy of a string that can be modified 
// without affecting the original string.  
// Doesn't check for NULL pointers, it assumes that input string is valid.
// The function does not handle memory management for the input string;
// Doesn't check if i/p string is NULL; simply returns NULL if it is. 
// Doesn't handle case where i/p string is empty; simply returns empty string
