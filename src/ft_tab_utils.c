/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   template.c											:+:		:+:	:+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2024/09/05 14:15:32 by nidionis			###   ########.fr		*/
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	append_tab(char ***tab_addr, char *str)
{
	size_t	len;
	char	**tab;
	char	**new_tab;

	tab = *tab_addr;
	len = ft_tablen(tab) + 1;
	if (!tab)
		new_tab = gc_malloc(&d.gc, sizeof(char *), 2);
	else
		new_tab = gc_malloc(&d.gc, sizeof(char *), len);
	if (!new_tab)
	{
		printf("[append_tab]malloc error\n");
		minishell_exit();
	}
	new_tab[len--] = NULL;
	new_tab[len] = str;
	if (tab)
	{
		while (len--)
			new_tab[len] = tab[len];
		gc_free_item(&d.gc, tab);
	}
	*tab_addr = new_tab;
}
