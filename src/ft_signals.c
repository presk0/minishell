/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/02/04 02:25:42 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	sigchld_handler(int sig)
{
	(void)sig;
	while (waitpid(-1, NULL, WNOHANG) > 0)
		continue ;
}

void	sig_default(void)
{
	struct sigaction	sa_quit;

	(void)sa_quit;
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
}

void	sig_ignores(void)
{
	struct sigaction	sa_quit;

	(void)sa_quit;
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

void	handle_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void	init_sig(t_data *d)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct sigaction	sa_child;

	(void)d;
	if (!g_child_opened)
	{
		sa_int.sa_handler = handle_sigint;
		sigemptyset(&sa_int.sa_mask);
		sigaction(SIGINT, &sa_int, NULL);
		sa_quit.sa_handler = SIG_IGN;
		sigemptyset(&sa_quit.sa_mask);
		sigaction(SIGQUIT, &sa_quit, NULL);
		sa_child.sa_handler = sigchld_handler;
		sigemptyset(&sa_child.sa_mask);
		//sa_child.sa_flags = SA_RESTART;
		sigaction(SIGCHLD, &sa_child, NULL);
	}
}
