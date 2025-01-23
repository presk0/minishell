/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/23 14:02:06 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_sig()
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("sigaction SIGINT");
		minishell_exit();
	}
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("sigaction SIGQUIT");
		minishell_exit();
	}
}

void handle_child_sigint(int sig)
{
	(void)sig;
	ft_errmsg("coucou");
}

void init_child_sig()
{
    struct sigaction sa;

    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_child_sigint;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1)
	{
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

void wait_for_child(pid_t pid)
{
    sigset_t mask, oldmask;
    int status;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    if (waitpid(pid, &status, 0) == -1)
	{
        perror("waitpid");
    }
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
}

