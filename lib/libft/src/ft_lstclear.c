/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*													+:+ +:+			+:+	 */
/*   By: nidionis <nidionis@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2022/03/09 19:31:49 by supersko			#+#	#+#			 */
/*   Updated: 2025/01/23 17:03:21 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_item;

	if (lst && del)
	{
		while (*lst)
		{
			next_item = (*lst)->next;
			ft_lstdelone(lst, del);
			*lst = next_item;
		}
	}
	else
		ft_errmsg("[ft_lstclear] lst or del functions is/are NULL\n");
}
