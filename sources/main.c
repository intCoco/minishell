/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:55:48 by chuchard          #+#    #+#             */
/*   Updated: 2024/03/15 22:27:30 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		ft_putstr_fd(PROMPT, 1);
	}
}

int	main(void)
{
	char *input;

	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	while (1)
	{
		input = readline(PROMPT);
		if (input == NULL)
			break ;
		if (ft_strcmp(input, "") != 0)
			add_history(input);
		if (ft_strcmp(input, "exit") == 0 || ft_strcmp(input, "quit") == 0)
			break ;
		printf("Commande exécutée : %s\n", input);
		free(input);
	}
	clear_history();
	printf("Fin de l'entrée standard.\n");
	return (0);
}