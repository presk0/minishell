/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/02/04 18:13:15 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigquit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "Quit", 1);
	rl_redisplay();
	while (waitpid(-1, NULL, WNOHANG) > 0)
		continue ;
}

void	sig_default(void)
{
	struct sigaction	sa_quit;

	(void)sa_quit;
	ft_bzero(&sa_quit, sizeof(sa_quit));
	signal(SIGINT, SIG_DFL);
	//signal(SIGTERM, SIG_DFL);
	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	sig_ignores(void)
{
	struct sigaction	sa_quit;

	(void)sa_quit;
	signal(SIGINT, SIG_IGN);
	//signal(SIGTERM, SIG_IGN);
}

void	handle_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
	while (waitpid(-1, NULL, WNOHANG) > 0)
		continue ;
}

//void	init_sig(t_data *d)
//{
//	struct sigaction	sa_int;
//	struct sigaction	sa_quit;
//
//	(void)d;
//	sa_int.sa_handler = handle_sigint;
//	sigemptyset(&sa_int.sa_mask);
//	sigaction(SIGINT, &sa_int, NULL);
//	sa_quit.sa_handler = SIG_IGN;
//	sigemptyset(&sa_quit.sa_mask);
//	sigaction(SIGQUIT, &sa_quit, NULL);
//}

void	init_sig(t_data *d)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	(void)d;
	ft_bzero(&sa_int, sizeof(sa_int));
	ft_bzero(&sa_quit, sizeof(sa_quit));

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

