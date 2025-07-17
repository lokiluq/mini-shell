/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportunset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:50:46 by lnul-hak          #+#    #+#             */
/*   Updated: 2024/10/01 18:01:16 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_valid_var(t_params *params, char *var, char *args,
		char *pointer)
{
	t_env	*node;

	if (is_valid_var(var) && var[0])
	{
		node = find_env_node(params->env_list, var);
		if (node)
		{
			free(node->value);
			node->value = ft_strdup(pointer + 1);
		}
		else
			append_env_list(&params->env_list, args);
	}
	else
	{
		params->exit_code = 1;
		error_messages(3, var, "export");
	}
}

void	export_handler(t_params *params, int i)
{
	char	*var;
	char	*pointer;
	char	**args;
	int		j;

	j = 1;
	args = params->data[i].args;
	while (args[j])
	{
		pointer = (strchr(args[j], '='));
		if (pointer)
		{
			var = ft_substr(args[j], 0, pointer - args[j]);
			check_valid_var(params, var, args[j], pointer);
			free(var);
		}
		j++;
	}
}			

int	is_valid_var(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] >= '0' && var[i] <= '9' && i == 0)
			return (0);
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	unset_handler(t_params *params, int i)
{
	t_env	*node;
	t_env	*prev;
	char	**args;
	int		j;

	j = 0;
	args = params->data[i].args;
	while (args[++j])
	{
		node = find_env_node(params->env_list, args[j]);
		if (!node)
			continue ;
		else if (node == params->env_list)
			params->env_list = node->next;
		else
		{
			prev = prev_env_node(params->env_list, node);
			prev->next = node->next;
		}
		free(node->variable);
		free(node->value);
		free(node);
		node = NULL;
	}
}

t_env	*prev_env_node(t_env *list, t_env *node)
{
	t_env	*prev;

	prev = NULL;
	while (list->next)
	{
		if (list->next->variable == node->variable)
			prev = list;
		list = list->next;
	}
	return (prev);
}
