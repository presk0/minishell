/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:41:30 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/01 17:16:36 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab_original)
{
	char	**tab_copy;
	size_t	tab_len;
	size_t	i;

	tab_len = ft_tablen(tab_original);
	tab_copy = malloc((tab_len + 1) * sizeof(char *));
	tab_copy[tab_len] = NULL;
	i = 0;
	while (i < tab_len)
	{
		tab_copy[i] = ft_strdup(tab_original[i]);
		if (!tab_copy[i])
		{
			ft_free_split(&tab_copy);
			return (NULL);
		}
		i++;
	}
	return (tab_copy);
}
