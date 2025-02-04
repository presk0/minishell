/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/04 00:50:15 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*gc_realloc(t_data *d, void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = gc_malloc(&d->gc, 1, new_size);
	if (!new_ptr)
	{
		perror("minishell: ft_realloc: malloc failed");
		return (NULL);
	}
	if (ptr)
	{
		if (new_size < old_size)
			new_size = old_size;
		ft_memcpy(new_ptr, ptr, new_size);
		gc_free_item(&d->gc, ptr);
	}
	return (new_ptr);
}

char	*gc_strjoin(t_data *d, const char *s1, const char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (!gc_append(&d->gc, ret))
		minishell_exit(d, "error", -1);
	return (ret);
}
