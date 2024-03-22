/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:55:48 by chuchard          #+#    #+#             */
/*   Updated: 2024/03/22 18:24:48 by chuchard         ###   ########.fr       */
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

void	print_info(t_minishell *ms, int k)
{
	printf("left avant = %s\n", ms->left);
	printf("token command = %s\n", ms->tokens[k].command);
	// printf("token input = %s\n", ms->tokens[k].input);
	// printf("token redir = %i\n", ms->tokens[k].redir);
	// printf("token redir = %s\n", ms->tokens[k].redir_target);
}

void	ft_tokenization(t_minishell *ms)
{
	printf("i = %i\n", ms->i);
	printf("j = %i\n", ms->j);
	if (ms->input[ms->i] == '\"')
	{
		printf("\" detected\n");
		while (ms->input[ms->i] && ms->input[ms->i] != '\"')
			ms->i++;
	}
	else
		while (ms->input[ms->i] && !ft_ischarset(ms->input[ms->i - 1], WHITESPACES)
			&& !ft_ischarset(ms->input[ms->i], METACHARS))
			ms->i++;
	if (ms->j == 0)
		ms->tokens[ms->j].command = ft_strndup(ms->input, ms->left - ms->input,
				ms->i);
	// if (j == 1)
	// 	ms->tokens[j].input = ft_strndup(ms->input, i, ms->left - ms->input);
	// if (j == 2)
	// 	ms->tokens[j].redir_target = ft_strndup(ms->input, i, ms->left - ms->input);
	// if (j == 3)
	// 	ms->tokens[j].input = ft_strndup(ms->input, i, ms->left - ms->input);
	print_info(ms, 0);
	ms->left += ms->i;
	printf("left apres = %s\n", ms->left);
	ms->j++;
}

void	ft_free(t_minishell *ms)
{
	while (ms->token_nb >= 0)
	{
		if (ms->tokens[ms->token_nb].command)
			free(ms->tokens[ms->token_nb].command);
		if (ms->tokens[ms->token_nb].input)
			free(ms->tokens[ms->token_nb].input);
		if (ms->tokens[ms->token_nb].redir_target)
			free(ms->tokens[ms->token_nb].redir_target);
		ms->token_nb--;
	}
	free(ms->tokens);
	free(ms->input);
	ft_bzero(ms->tokens, sizeof(t_token));
}

int	treat(t_minishell *ms)
{
	ms->i = 0;
	ms->j = 0;
	ms->tokens = ft_calloc(sizeof(t_token), 1);
	if (!ms->tokens)
		return (0);
	ft_strtrim_ws(ms->input);
	ms->left = ms->input;
	// while (ms->left)
	ft_tokenization(ms);
	printf("Commande exécutée : %s\n", ms->input);
	return 1;
}

int	main(void)
{
	t_minishell ms;

	ft_bzero(&ms, sizeof(t_minishell));
	ft_bzero(&ms, sizeof(t_minishell));
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	while (1)
	{
		ms.input = readline(PROMPT);
		if (ms.input == NULL)
			break ;
		if (ft_strcmp(ms.input, "") != 0)
			add_history(ms.input);
		if (!ft_strcmp(ms.input, "exit") || !ft_strcmp(ms.input, "quit"))
			break ;
		if(!treat(&ms))
			break ;
		ft_free(&ms);
	}
	rl_clear_history();
	printf("Fin de l'entrée standard.\n");
	return (0);
}
