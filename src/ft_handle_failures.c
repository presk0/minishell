/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_failures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/04 00:09:15 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_dup_failure(int fd, const char *msg)
{
	if (fd == -1)
		perror(msg);
}

void	handle_fork_failure(pid_t pid, const char *msg)
{
	if (pid == -1)
		perror(msg);
}

void	handle_pipe_failure(int result, const char *msg)
{
	if (result == -1)
		perror(msg);
}
