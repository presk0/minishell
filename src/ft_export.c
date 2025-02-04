/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/03 23:36:35 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_export(char **tab)
{
	char	**t;
	size_t	i;

	t = ft_tabdup(tab);
	ft_easy_sort(&t);
	i = 0;
	while (t[i])
		printf("declare -x %s\n", t[i++]);
	ft_free_split(&t);
}

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_easy_sort(char ***t)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	**tab;

	tab = *t;
	if (tab == NULL)
		return ;
	len = ft_tablen(tab);
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i++)
		{
			if (ft_strcmp(tab[j], tab[j + 1]) > 0)
				ft_swap(&tab[j], &tab[j + 1]);
			j++;
		}
	}
}

int	ft_export(t_data *d, t_token *token)
{
	int	i;

	if (!token->args[1])
	{
		print_export(d->env);
		return (CLEAN_EXIT);
	}
	i = 1;
	while (token->args[i] != NULL)
		ft_setenv(d, token->args[i++]);
	d->status = CLEAN_EXIT;
	return (CLEAN_EXIT);
}
