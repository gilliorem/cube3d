/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:11:01 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/14 13:11:01 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* static void	sample_ft(unsigned int i, char *s)
{
	write(1, &s[i], 1);
}

static void	to_uppercase(unsigned int i, char *s)
{
	if (s[i] >= 'a' && s[i] <= 'z')
		s[i] -= 32;
} */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/* int	main(void)
{
	char	str[] = "Hello, World!";
	ft_striteri(str, to_uppercase);
	ft_striteri(str, sample_ft);
	return (0);
}*/

//Applies a function f to each character of the string s,
// index of character is first argument and pointer to character is the second
// Modifies the string in place. Function f is a pointer to a function 
// Iterates through the string s, calling f for each character

// Useful for applying a transformation to each char of a string, (uppercasing)
// Doesn't check if s is NULL; it assumes caller will provide valid string.
// Doesn't handle memory management; assumes caller will manage the memory.
// Doesn't check if function f is NULL; assumes caller provides valid function
// Doesn't handle when string s is empty; simply returns without doing anything
// Typically used in str manipulation tasks, formatting or transforming strs.
