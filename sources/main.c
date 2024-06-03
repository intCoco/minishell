/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:55:48 by chuchard          #+#    #+#             */
/*   Updated: 2024/06/03 18:36:34 by chuchard         ###   ########.fr       */
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

void print_info(t_input *input)
{
    t_token *current = input->tokens;
    
    while (current)
    {
        printf("Token: %s, Type: %d\n", current->value, current->type);
        current = current->next;
    }
    printf("Reste à traiter : %s\n\n", input->left);
}

// void print_info(t_input *input, int k)
// {
//     t_token *current = input->tokens;
//     int count = 0;

//     while (current && count < k)
//     {
//         current = current->next;
//         count++;
//     }
//     if (current)
//     {
//         printf("left avant = %s\n", input->left);
//         printf("token command = %s\n", current->value);
//     }
//     else
//     {
//         printf("Token not found.\n");
//     }
// }

t_token *new_token(char *value, t_token_type type)
{
    t_token *new = malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->value = value;
    new->type = type;
    new->next = NULL;
    return (new);
}

void add_token(t_input *input, t_token *new)
{
    t_token *tmp;

    if (!input->tokens)
    {
        input->tokens = new;
    }
    else
    {
        tmp = input->tokens;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

void free_tokens(t_token *tokens)
{
    t_token *tmp;

    while (tokens)
    {
        tmp = tokens;
        tokens = tokens->next;
        if (tmp->value)
            free(tmp->value);
        free(tmp);
    }
}

void ft_free_input_data(t_input *input)
{
    free_tokens(input->tokens);
    if (input->total)
        free(input->total);
    input->tokens = NULL;
}

void ft_tokenization(t_input *input)
{
    t_token_type type = COMMAND;
    
    while (input->left[input->i])
    {
        if (!input->left[input->i])
            break;
        while (input->left[input->i] && 
               !ft_ischarset(input->left[input->i], WHITESPACES) &&
               (!ft_ischarset(input->left[input->i], METACHARS) || 
                (input->i > 0 && input->left[input->i - 1] == '\\')))
        {
            if (input->left[input->i] == '\'' || input->left[input->i] == '\"')
            {
                printf("' detected\n");
                input->i++;
                while (input->left[input->i] && input->left[input->i] != *input->left)
                    input->i++;
                if (!input->left[input->i])
                {
                    ft_putendl_fd("Unclosed quotes.", 2);
                    return;
                }
            }
            // else if (ft_ischarset(input->left[input->i], METACHARS))
            // {
            //     if (input->i == start)
            //     {
            //         type = REDIRECTION; // ou PIPE, selon ton traitement
            //         input->i++;
            //     }
            //     break;
            // }
            input->i++;
        }
        add_token(input, new_token(ft_strndup(input->left, 0, input->i), type));
        if (input->left[input->i] == ' ')
		    input->i++;
        input->left += input->i;
        print_info(input);
        input->i = 0;
    }
}


// void ft_tokenization(t_input *input)
// {
//     printf("i = %i\n", input->i);
//     printf("j = %i\n", input->j);
//     while (input->left[input->i] && !ft_ischarset(input->left[input->i], WHITESPACES) &&
//            (!ft_ischarset(input->left[input->i], METACHARS) || 
//            (input->i > 0 && input->left[input->i - 1] == '\\')))
//     {
//         if (input->left[input->i] == '\'' || input->left[input->i] == '\"')
//         {
//             printf("' detected\n");
//             input->i++;
//             while (input->left[input->i] && input->left[input->i] != *input->left)
//                 input->i++;
//             if (!input->left[input->i])
//             {
//                 ft_putendl_fd("Unclosed quotes.", 2);
//                 return;
//             }
//         }
//         input->i++;
//     }
//     char *value = ft_strndup(input->left, 0, input->i - (input->left - input->total));
//     t_token *new_tkn = new_token(value, COMMAND);
//     add_token(input, new_tkn);
//     // if (input->left[input->i] == ' ')
//     //     input->i++;
//     print_info(input, 0);
//     input->left += input->i;
//     printf("left apres = %s\n", input->left);
//     input->j++;
// }

int ft_treat_input(t_input *input)
{
    ft_bzero(input, sizeof(t_input));
    input->total = readline(PROMPT);
    if (input->total == NULL)
        return (0);
    if (ft_strcmp(input->total, "") != 0)
        add_history(input->total);
    ft_strtrim_ws(input->total);
    if (!ft_strcmp(input->total, "exit") || !ft_strcmp(input->total, "quit"))
        return (0);
    input->i = 0;
    input->j = 0;
	input->token_nb = 0;
    input->tokens = NULL;
    input->left = input->total;
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