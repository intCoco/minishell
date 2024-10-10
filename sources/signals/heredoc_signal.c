/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:53:07 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/10 07:13:37 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc_sig(int sig)
{
	(void)sig;
	g_signal = 1;
	rl_done = 1;
	write(STDOUT_FILENO, "\n", 1);
	printf("%s", PROMPT);
}

void	heredoc_signal(void)
{
	signal(SIGINT, heredoc_sig);
	signal(SIGQUIT, handle_sig);
}
