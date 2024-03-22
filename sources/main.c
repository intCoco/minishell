/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:55:48 by chuchard          #+#    #+#             */
/*   Updated: 2024/03/22 18:55:19 by chuchard         ###   ########.fr       */
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

char	*ft_strtrim_ws(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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
				break ;
		}
		s[j++] = s[i++];
	}
	s[j] = 0;
	return (s);
}

void	print_info(t_input *input, int k)
{
	printf("left avant = %s\n", input->left);
	printf("token command = %s\n", input->tokens[k].command);
	// printf("token input = %s\n", input->tokens[k].input);
	// printf("token redir = %i\n", input->tokens[k].redir);
	// printf("token redir = %s\n", input->tokens[k].redir_target);
}

void	ft_tokenization(t_input *input)
{
	printf("i = %i\n", input->i);
	printf("j = %i\n", input->j);
	if (input->total[input->i] == '\"')
	{
		printf("\" detected\n");
		input->i++;
		input->left++;
		while (input->total[input->i] && input->total[input->i] != '\"')
			input->i++;
		if (!input->total[input->i])
		{
			ft_putendl_fd("Unclosed quotes.", 2);
			return ;
		}
	}
	else
		while (input->total[input->i] && !ft_ischarset(input->total[input->i
				- 1], WHITESPACES) && !ft_ischarset(input->total[input->i],
				METACHARS))
			input->i++;
	printf("i=%i\n", input->i);
	if (input->j == 0)
		input->tokens[input->j].command = ft_strndup(input->total, input->left
				- input->total, input->i);
	// if (j == 1)
	// 	input->tokens[j].input = ft_strndup(input->total, i, input->left - input->total);
	// if (j == 2)
	// 	input->tokens[j].redir_target = ft_strndup(input->total, i, input->left - input->total);
	// if (j == 3)
	// 	input->tokens[j].input = ft_strndup(input->total, i, input->left - input->total);
	print_info(input, 0);
	input->left += input->i;
	printf("left apres = %s\n", input->left);
	input->j++;
}

void	ft_free_input_data(t_input *input)
{
	while (input->token_nb >= 0)
	{
		if (input->tokens[input->token_nb].command)
			free(input->tokens[input->token_nb].command);
		if (input->tokens[input->token_nb].input)
			free(input->tokens[input->token_nb].input);
		if (input->tokens[input->token_nb].redir_target)
			free(input->tokens[input->token_nb].redir_target);
		input->token_nb--;
	}
	free(input->tokens);
	free(input->total);
	ft_bzero(input->tokens, sizeof(t_token));
}

int	ft_treat_input(t_input *input)
{
	ft_bzero(input, sizeof(t_input));
	input->total = readline(PROMPT);
	if (input->total == NULL)
		return (0);
	if (ft_strcmp(input->total, "") != 0)
		add_history(input->total);
	if (!ft_strcmp(input->total, "exit") || !ft_strcmp(input->total, "quit"))
		return (0);
	input->i = 0;
	input->j = 0;
	input->tokens = ft_calloc(sizeof(t_token), 1);
	if (!input->tokens)
		return (0);
	ft_strtrim_ws(input->total);
	input->left = input->total;
	// while (input->left)
	ft_tokenization(input);
	printf("Commande exécutée : %s\n", input->total);
	return (1);
}

int	main(void)
{
	t_minishell ms;

	ft_bzero(&ms, sizeof(t_minishell));
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	while (1)
	{
		if (!ft_treat_input(&ms.input))
			break ;
		ft_free_input_data(&ms.input);
	}
	rl_clear_history();
	printf("Fin de l'entrée standard.\n");
	return (0);
}