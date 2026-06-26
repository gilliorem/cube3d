/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:16:25 by mohikhan          #+#    #+#             */
/*   Updated: 2025/05/24 20:23:58 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_countandreplace(char *s, char delimiter)
{
	bool	new_word;
	char	*temp;
	int		count;

	new_word = false;
	temp = s;
	count = 0;
	while (*temp)
	{
		if (*temp != delimiter && new_word == false)
		{
			new_word = true;
			count++;
		}
		else if (*temp == delimiter)
		{
			*temp = '\0';
			new_word = false;
		}
		temp++;
	}
	return (count);
}

static bool	fill_ptr(char **ptr, char *s1, int wc)
{
	int	i;

	i = 0;
	while (i < wc)
	{
		if (*s1)
		{
			ptr[i++] = ft_strdup(s1);
			if (!ptr[i - 1])
			{
				while (--i >= 0)
					free(ptr[i]);
				free(ptr);
				return (false);
			}
			while (*s1)
				s1++;
		}
		s1++;
	}
	ptr[i] = NULL;
	return (true);
}

char	**ft_split(char const *s, char c)
{
	char	*s1;
	char	**ptr;
	int		wc;

	if (!s)
		return (NULL);
	s1 = ft_strdup(s);
	if (!s1)
		return (NULL);
	wc = word_countandreplace(s1, c);
	ptr = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!ptr)
	{
		free(s1);
		return (NULL);
	}
	if (!fill_ptr(ptr, s1, wc))
	{
		free (s1);
		return (NULL);
	}
	free(s1);
	return (ptr);
}

/* int	main(void)
{
	char	*str;
	char	**twod;
	int		i;

	str = ",,This,works,,like,a,charm,";
	twod = ft_split(str, ',');
	i = 0;
	while (twod[i])
		printf("%s\n", twod[i++]);
	return (0);
} */

// Splits a string into an array of strings based on a delimiter.
// // It takes a string s and a character c as arguments.
// First duplicate the input string to avoid modifying the original.
// Then counts the number of words by replacing delimiters with null characters.
// Allocate memory for an array of strings and fills it with the split words.
// Free the duplicated string and return the array of strings.