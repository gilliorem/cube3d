/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:17:04 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/14 13:17:04 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* char	next_char(unsigned int i, char c)
{
	(void)i;
	return (c + 1);
} */

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (!s || !f)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/* int	main(void)
{
	char	*str;
	char	*result;

	str = "123";
	result = ft_strmapi(str, next_char);
	printf("%s\n", result);
	free(result);
	return (0);
} */

// Applies a function to each character of a string
// passes the index of character as 1st argu and the character itself as the 2nd
// Returns new string created by applying the f to each char of the original str
// f is a pointer to a function that takes an unsigned int and a char as args
// Iterates through s, calling f for each character & storing result in new str
// Memory for the new string is allocated using malloc, caller must free it