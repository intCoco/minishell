/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:25:47 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/10 16:17:47 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	without_args(t_exec *ex)
{
	int		i;
	char	**tab_ptr;
	int		count;

	i = 0;
	count = 0;
	while (ex->env[count])
		count++;
	tab_ptr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab_ptr)
		return ;
	while (i < count)
	{
		tab_ptr[i] = ex->env[i];
		i++;
	}
	tab_ptr[i] = NULL;
	sort_ex(tab_ptr, count);
	print_export(tab_ptr, count);
	free(tab_ptr);
}

static int	get_index(t_exec *ex, char *var)
{
	int			i;
	size_t		len;
	char		*check_sign;

	i = 0;
	check_sign = ft_strchr(var, '=');
	if (check_sign)
		len = check_sign - var;
	else
		len = ft_strlen(var);
	while (ex->env[i])
	{
		if (ft_strncmp(ex->env[i], var, len) == 0 && ex->env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	make_update_env(t_exec *ex, char *var)
{
	int		index;
	char	*new_var;

	new_var = make_quotes(var);
	if (!new_var)
		return (1);
	index = get_index(ex, var);
	if (index != -1)
	{
		free(ex->env[index]);
		ex->env[index] = new_var;
	}
	else
	{
		index = 0;
		while (ex->env[index])
			index++;
		index--;
		ex->env = custom_realloc(ex->env, index + 1, index + 2);
		ex->env[index + 1] = new_var;
		ex->env[index + 2] = NULL;
	}
	return (0);
}

int	make_export(t_token *data, t_exec *ex)
{
	char	*tmp;

	if (!data->next)
	{
		without_args(ex);
		return (0);
	}
	while (data->next)
	{
		if (ft_strncmp(data->next->value, "=", 1) == 0)
		{
			ft_putstr_fd("Minishell: export: `", 2);
			ft_putstr_fd(data->next->value, 2);
			ft_putstr_fd("': not a valid indentifier\n", 2);
			return (1);
		}
		if (!ft_strchr(data->next->value, '='))
			tmp = ft_strjoin(data->next->value, "=");
		else
			tmp = ft_strdup(data->next->value);
		make_update_env(ex, tmp);
		data = data->next;
		free(tmp);
	}
	return (0);
}
