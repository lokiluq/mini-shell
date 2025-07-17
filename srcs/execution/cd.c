/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:48:12 by lnul-hak          #+#    #+#             */
/*   Updated: 2024/10/02 17:49:00 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd_args(t_params *params, int i)
{
	char	**args;
	t_env	*env_node;

	args = params->data[i].args;
	if (args[1] && args[2])
	{
		error_messages(1, NULL, "cd");
		params->exit_code = 1;
		return (NULL);
	}
	if (!args[1] || !ft_strncmp(args[1], "~", 2))
	{
		env_node = find_env_node(params->env_list, "HOME");
		if (!env_node || !env_node->value[0])
		{	
			error_messages(5, NULL, "cd");
			return (NULL);
		}
		return (env_node->value);
	}
	else
		return (args[1]);
}

static	void	update_cd_path(t_params *params, char *cwd, char *state)
{
	t_env	*env_node;
	char	*modstate;

	modstate = ft_strchr(state, '=');
	*modstate = '\0';
	env_node = find_env_node(params->env_list, state);
	if (env_node)
	{
		free(env_node->value);
		env_node->value = cwd;
	}
	else
	{
		*modstate = '=';
		modstate = ft_strjoin(state, cwd);
		append_env_list(&params->env_list, modstate);
		free(cwd);
		free(modstate);
	}
}

void	cd_handler(t_params *params, int i)
{
	char	*cwd;
	char	*new_dir;
	char	**args;

	args = params->data[i].args;
	new_dir = cd_args(params, i);
	if (!new_dir)
		return ;
	cwd = getcwd(NULL, 1000);
	if (chdir(new_dir) != 0)
	{
		error_messages(2, args[1], "cd");
		params->exit_code = 1;
		free(cwd);
		return ;
	}
	update_cd_path(params, cwd, (char []){"OLDPWD="});
	update_cd_path(params, getcwd(NULL, 1000), (char []){"PWD="});
}
