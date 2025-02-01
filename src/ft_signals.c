/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/24 00:34:14 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigquit_forked(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "Quit\n", 6);
	minishell_exit("init_sig", STATUS_SIGQUIT);
}	

void	forked_sig(void)
{
	struct sigaction	sa_quit;

	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		perror("Erreur lors de la réinitialisation de SIGINT");
	if (signal(SIGTERM, SIG_DFL) == SIG_ERR)
		perror("Erreur lors de la réinitialisation de SIGTERM");
	sa_quit.sa_handler = handle_sigquit_forked;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		minishell_exit("init_sig", STATUS_SIGQUIT);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_d.sigint_received = 1;
}

void	init_sig(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("sigaction SIGINT");
		minishell_exit("[init_sig]", -1);
	}
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		minishell_exit("init_sig", -1);
}

void	wait_for_child(pid_t pid)
{
	if (waitpid(pid, &g_d.status, 0) == -1)
		perror("waitpid");
}
