#include "libft.h"
char	*gnl_strjoin(char *s1, char *s2)
{
	char	*str_join;
	ssize_t	str_join_len;
	ssize_t	i;

	str_join_len = ft_strlen(s1) + ft_strlen(s2);
	str_join = (char *)malloc((str_join_len + 1) * sizeof(char));
	if (!str_join)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str_join[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str_join[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	str_join[ft_strlen(s1) + i] = '\0';
	free(s1);
	return (str_join);
}
