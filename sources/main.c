/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:55:48 by chuchard          #+#    #+#             */
/*   Updated: 2024/03/20 18:59:53 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		ft_putstr_fd(PROMPT, 1);
	}
}

char *ft_strtrim_ws(char *s)
{
	int i = 0;
	int j = 0;

	while (s[i] && ft_ischarset(s[i], WHITESPACES))
		i++;
	while (s[i])
	{
		if (ft_ischarset(s[i], WHITESPACES))
		{
			while (s[i] && ft_ischarset(s[i], WHITESPACES))
				i++;
			if (s[i])
				s[j++] = ' ';
			else
				break;
		}
		s[j++] = s[i++];
	}
	s[j] = 0;
	return (s);
}

// void tokenization(char *input)
// {
// 	t_token token;
// 	char *split;
// 	int i = 0;

// 	// split = ft_split(input, CHARSET);
// 	// token.command = split[0];
// 	// while (split[i])token.input =
	
// }

int main(void)
{
	char *input;

	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	while (1)
	{
		input = readline(PROMPT);
		if (input == NULL)
			break;
		if (ft_strcmp(input, "") != 0)
			add_history(input);
		if (ft_strcmp(input, "exit") == 0 || ft_strcmp(input, "quit") == 0)
			break;
		ft_strtrim_ws(input);
		printf("Commande exécutée : %s\n", input);
		free(input);
	}
	clear_history();
	printf("Fin de l'entrée standard.\n");
	return (0);
}