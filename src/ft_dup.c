/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/27 22:27:35 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	reset_stdin(int stdin_fd)
{
	if (dup2(stdin_fd, STDIN_FILENO) == -1)
		minishell_exit("[rec_exec] dup2 failed", -1);
}

void	save_stds(int *saved_std)
{
	saved_std[IN] = dup(STDIN_FILENO);
	saved_std[OUT] = dup(STDOUT_FILENO);
	saved_std[ERR] = dup(STDERR_FILENO);
	handle_dup_failure(saved_std[IN], "[execute_command] dup failed");
	handle_dup_failure(saved_std[OUT], "[execute_command] dup failed");
	handle_dup_failure(saved_std[ERR], "[execute_command] dup failed");
}

void	restore_stds(int *saved_std)
{
	dup2(saved_std[IN], STDIN_FILENO);
	dup2(saved_std[OUT], STDOUT_FILENO);
	dup2(saved_std[ERR], STDERR_FILENO);
	close(saved_std[IN]);
	close(saved_std[OUT]);
	close(saved_std[ERR]);
}