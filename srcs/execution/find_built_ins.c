/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_built_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:10:00 by lnul-hak          #+#    #+#             */
/*   Updated: 2024/10/01 18:06:07 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_built_in(char *str)
{
	if (!str)
		return (7);
	if (!ft_strncmp(str, "echo", 5))
		return (0);
	if (!ft_strncmp(str, "pwd", 4))
		return (1);
	if (!ft_strncmp(str, "env", 4))
		return (2);
	if (!ft_strncmp(str, "cd", 3))
		return (3);
	if (!ft_strncmp(str, "export", 7))
		return (4);
	if (!ft_strncmp(str, "unset", 6))
		return (5);
	if (!ft_strncmp(str, "exit", 5))
		return (6);
	return (7);
}

void	error_messages(int i, char *str, char *builtin)
{	
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(builtin, 2);
	if (i == 1)
		ft_putstr_fd(": too many arguments\n", 2);
	else if (i == 2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (i == 3)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
	}
	else if (i == 4)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (i == 5)
		ft_putstr_fd(": HOME not set\n", 2);
}

void	exec_builtin(t_params *params, int i, int built_idx)
{
	static void	(*builtins[7])(t_params *, int)
		=	{	
		echo_handler,
		pwd_handler,
		env_handler,
		cd_handler,
		export_handler,
		unset_handler,
		exit_handler,
	};

	(*builtins[built_idx])(params, i);
}
