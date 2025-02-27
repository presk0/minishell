/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_tab_utils.c                                     :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/02/04 00:22:27 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	append_tab(t_data *d, char ***tab_addr, char *str)
{
	size_t	len;
	char	**tab;
	char	**new_tab;

	tab = *tab_addr;
	len = ft_tablen(tab) + 1;
	if (!tab)
		new_tab = gc_malloc(&d->gc, sizeof(char *), 2);
	else
		new_tab = gc_malloc(&d->gc, sizeof(char *), len + 1);
	if (!new_tab)
		minishell_exit(d, "[append_tab]", -1);
	new_tab[len--] = NULL;
	new_tab[len] = str;
	if (tab)
	{
		while (len--)
			new_tab[len] = tab[len];
		gc_free_item(&d->gc, tab);
	}
	*tab_addr = new_tab;
}

char	**duplicate_tab(t_data *d, char **tab_original)
{
	char	**tab_copy;
	size_t	tab_len;
	size_t	i;

	tab_len = ft_tablen(tab_original);
	tab_copy = gc_malloc(&d->gc, (tab_len + 1), sizeof(char *));
	tab_copy[tab_len] = NULL;
	i = 0;
	while (i < tab_len)
	{
		tab_copy[i] = gc_strdup(&d->gc, tab_original[i]);
		if (!tab_copy[i])
			minishell_exit(d, "[duplicate_tab]", ERR_GC_STRDUP);
		i++;
	}
	return (tab_copy);
}
