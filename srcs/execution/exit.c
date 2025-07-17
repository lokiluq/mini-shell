/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:53:40 by lnul-hak          #+#    #+#             */
/*   Updated: 2024/10/01 17:55:42 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_handler(t_params *params, int i)
{
	char	**args;

	args = params->data[i].args;
	params->exit_code = 0;
	ft_putstr_fd("exit\n", 2);
	if (args[1])
	{
		if (args[2])
		{
			params->exit_code = 1;
			error_messages(1, NULL, "exit");
			return ;
		}
		if (is_it_number(args[1]) == 0)
			params->exit_code = ft_atoi(args[1]);
		else
		{
			error_messages(4, args[1], "exit");
			params->exit_code = 2;
		}
	}
	free_all(params);
	free_env_list(params->env_list);
	exit(params->exit_code);
}

int	is_it_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}
