/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_duplicate_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/27 17:31:25 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	**ft_duplicate_tab(char **tab_original)
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