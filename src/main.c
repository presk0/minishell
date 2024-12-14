/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/12/14 16:44:12 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	minishell(void)
{
	char	*line;

	while (1)
	{
		line = readline(PS1);
		if (!line)
			break ;
		printf("%s\n", line);
		add_history(line);
		free(line);
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	minishell();
	return (0);
}

