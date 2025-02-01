/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_wd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:09:43 by supersko          #+#    #+#             */
/*   Updated: 2022/05/15 22:29:05 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_next_wd(char *sentence, char sep)
{
	if (!(*sentence))
		sentence = NULL;
	else
		while (*sentence && *sentence != sep)
			sentence++;
	if (*sentence == sep)
		while (*sentence == sep)
			sentence++;
	return (sentence);
}
