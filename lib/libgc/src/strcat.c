/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/28 00:27:46 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libgc.h>

size_t	gc_strcat(t_list **gc, char **result, char *str)
{
	size_t	result_new_len;
	char	*original_result;

	original_result = *result;
	result_new_len = ft_strlen(*result) + ft_strlen(str);
	*result = gc_strldup(gc, *result, result_new_len + 1);
	gc_free_item(gc, original_result);
	if (!*result)
	{
		perror("[gc_strlcat]");
		return (-1);
	}
	return (ft_strlcat(*result, str, result_new_len + 1));
}

size_t	gc_strlcat(t_list **gc, char **result, char *str, size_t l)
{
	char	*original_result;

	original_result = *result;
	*result = gc_strldup(gc, *result, l + 1);
	gc_free_item(gc, original_result);
	if (!*result)
	{
		perror("[gc_strlcat]");
		return (-1);
	}
	return (ft_strlcat(*result, str, l + 1));
}

char	*gc_strldup(t_list **gc, char *str, size_t len)
{
	void	*ret;

	ret = gc_malloc(gc, len + 1, 1);
	if (!ret)
	{
		ft_errmsg("[gc_strldup] gc_malloc returns NULL\n");
		gc_free_all(gc);
		return (NULL);
	}
	if (str)
		ft_strlcpy(ret, str, len + 1);
	return (ret);
}
