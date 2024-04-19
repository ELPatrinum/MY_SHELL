/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:11:06 by muel-bak          #+#    #+#             */
/*   Updated: 2024/03/13 14:08:07 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handleint(int code)
{
	(void)code;
	write(1, "\n", 1);
}

void	sig_int(int code)
{
	if (code == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_here_flag[1] = 1;
	}
}

void	sig_herdoc(int code)
{
	if (code == SIGINT)
	{
		g_here_flag[0] = 1;
		close(0);
	}
}

void	reset_terminal(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		exit(EXIT_FAILURE);
	term.c_iflag = ICRNL;
	term.c_oflag = OPOST | ONLCR;
	term.c_cflag = CS8 | CREAD;
	term.c_lflag = ISIG | ICANON | ECHO | ECHOE | ECHOK;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		exit(EXIT_FAILURE);
}
