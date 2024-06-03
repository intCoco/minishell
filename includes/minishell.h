/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 22:26:45 by chuchard          #+#    #+#             */
/*   Updated: 2024/06/03 18:03:31 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define PROMPT "\033[1;34mminishell\033[0m> "
# define WHITESPACES " \t\v\n\r"
# define METACHARS "><;"

typedef enum e_token_type
{
    COMMAND,
    PIPE,
    REDIRECTION,
} t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}			t_token;

typedef struct
{
	char	*total;
	char	*left;
	int		token_nb;
	int		i;
	int		j;
	t_token	*tokens;
}			t_input;

typedef struct
{
	t_input	input;
}			t_minishell;

#endif
