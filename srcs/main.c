/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:55:48 by chuchard          #+#    #+#             */
/*   Updated: 2024/03/15 22:04:27 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../libft/includes/libft.h"

typedef struct
{
	int type;    // Type de token
	char *value; // Valeur du token (le texte réel du token)
}		t_token;

void	handle_sig(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n\033[1;34mminishell\033[0m> ", 1);
}

int	main(void)
{
	char *input;
	
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	while (1)
	{
		input = readline("\033[1;34mminishell\033[0m> ");
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