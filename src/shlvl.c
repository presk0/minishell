/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:38:00 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/04 00:53:14 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	inc_shlvl(t_data *d)
{
	int		shlvl;
	char	*shlvl_str;
	char	*shlvl_line;

	shlvl_str = ft_getenv(d, "SHLVL");
	shlvl = ft_atoi(shlvl_str);
	shlvl++;
	shlvl_str = ft_itoa(shlvl);
	shlvl_line = gc_strdup(&d->gc, "SHLVL=");
	gc_strcat(&d->gc, &shlvl_line, shlvl_str);
	free(shlvl_str);
	ft_setenv(d, shlvl_line);
}
