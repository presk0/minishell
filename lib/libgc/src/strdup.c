/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/28 00:03:34 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libgc.h>

char	*gc_strndup(t_list **gc_addr, char *str, size_t n)
{
	char	*ret;

	ret = NULL;
	ret = gc_malloc(gc_addr, n + 1, 1);
	if (!ret)
		gc_free_all(gc_addr);
	else
		ft_strlcpy(ret, str, n + 1);
	return (ret);
}

char	*gc_strdup(t_list **gc_addr, char *str)
{
	char	*ret;
	size_t	len;

	ret = NULL;
	len = ft_strlen(str);
	ret = gc_malloc(gc_addr, ++len, 1);
	if (!ret)
		gc_free_all(gc_addr);
	else
		ft_strlcpy(ret, str, len);
	return (ret);
}
