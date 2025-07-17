/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:52:13 by lnul-hak          #+#    #+#             */
/*   Updated: 2024/10/01 18:23:55 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	valid_path(t_params *params, char **path_array, int i, int j)
{
	char	*backslash;
	char	*str;

	backslash = ft_strrchr(path_array[j], '/');
	if (backslash != NULL && *(backslash + 1) != '\0')
	{
		backslash = ft_strjoin(path_array[j], "/");
		free(path_array[j]);
		path_array[j] = backslash;
	}
	str = ft_strjoin(path_array[j], params->data[i].args[0]);
	if (access(str, F_OK | X_OK) == 0)
	{
		free(params->data[i].args[0]);
		params->data[i].args[0] = str;
		return (true);
	}
	free(str);
	return (false);
}

void	find_command_path(t_params *params, int i)
{
	t_env	*path;
	char	**path_array;
	int		j;

	j = 0;
	path = NULL;
	if (params->data[i].args[0][0] && !ft_strchr(params->data[i].args[0], '/'))
		path = find_env_node(params->env_list, "PATH");
	if (path == NULL)
		return ;
	path_array = ft_split(path->value, ':');
	while (path_array[j])
	{
		if (valid_path(params, path_array, i, j))
			break ;
		j++;
	}
	free_array(path_array);
}

t_env	*find_env_node(t_env *list, char *str)
{
	while (list)
	{
		if (!ft_strncmp(list->variable, str, ft_strlen(str) + 1))
			return (list);
		list = list->next;
	}
	return (NULL);
}
