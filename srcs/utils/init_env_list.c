/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:52:12 by lnul-hak          #+#    #+#             */
/*   Updated: 2024/10/01 15:11:57 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env_list(char **env)
{
	t_env	*head_env;

	head_env = NULL;
	while (*env)
	{
		append_env_list(&head_env, *env);
		env++;
	}
	return (head_env);
}

t_env	*init_env_node(char *str)
{
	t_env	*node;
	char	*res;
	int		i;

	i = 0;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	res = ft_strchr(str, '=');
	while (str + i != res)
		i++;
	node->variable = malloc(sizeof(char) * i + 1);
	ft_strlcpy(node->variable, str, i + 1);
	node->value = ft_strdup(res + 1);
	node->next = NULL;
	return (node);
}

void	append_env_list(t_env **head, char *env)
{
	t_env	*node;

	node = init_env_node(env);
	if (!node)
		exit(1);
	if (!(*head))
		*head = node;
	else
		find_last_env_node(*head)->next = node;
}

t_env	*find_last_env_node(t_env *head)
{
	while (head->next)
		head = head->next;
	return (head);
}
