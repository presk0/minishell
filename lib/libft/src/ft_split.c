/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:31:55 by supersko          #+#    #+#             */
/*   Updated: 2025/02/01 17:10:17 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

void	ft_free_split(char ***t)
{
	char	**tab;
	char	**temp;

	if (!t || !*t)
		return ;
	tab = *t;
	temp = tab;
	while (*tab)
	{
		free(*tab);
		*tab = NULL;
		tab++;
	}
	free(temp);
	*t = NULL;
}

/*
void	ft_free_split(char ***t)
{
	char	**tab;

	tab = *t;
	if (tab)
	{
		while (*tab)
		{
			free(*tab);
			*tab++ = NULL;
		}
		free(tab);
	}
	tab = NULL;
}
*/

static size_t	append_line(char *str, char sep, char **ret, size_t i_wd)
{
	size_t	wd_len;

	if (!str)
		return (0);
	wd_len = 0;
	while (str[wd_len] && str[wd_len] != sep)
		wd_len++;
	ret[i_wd] = malloc((wd_len + 1) * sizeof(char));
	if (ret[i_wd])
		ft_strlcpy(ret[i_wd], str, wd_len + 1);
	else
		ft_free_split(&ret);
	return (wd_len);
}

static char	**make_tab(char **ret, char const *s, char sep, unsigned int nb_wd)
{
	size_t	i_wd;
	size_t	wd_len;

	i_wd = 0;
	while (i_wd < nb_wd)
	{
		if (sep)
			while (*s == sep)
				s++;
		wd_len = append_line((char *)s, sep, ret, i_wd);
		if (!ret || !ret[i_wd++])
		{
			ft_free_split(&ret);
			return (NULL);
		}
		s += wd_len;
	}
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char			**ret;
	unsigned int	nb_wd;

	if (!s)
	{
		write(2, "try to split a NULL\n", 20);
		return (NULL);
	}
	nb_wd = ft_wd_count((char *)s, c);
	ret = (char **)malloc((nb_wd + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	ret[nb_wd] = NULL;
	ret = make_tab(ret, s, c, nb_wd);
	return (ret);
}
