/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:15:50 by cbaey             #+#    #+#             */
/*   Updated: 2024/10/02 15:13:39 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_params *params)
{
	if (params->token_list != NULL)
		free_list(&params->token_list);
	params->token_list = NULL;
	if (params->read_line != NULL)
		free(params->read_line);
	params->read_line = NULL;
	if (params->data != NULL)
		free_data(params);
}

void	free_data(t_params *params)
{
	int	i;

	i = 0;
	while (i < params->no_of_commands)
	{
		if (params->data[i].args != NULL)
		{
			if (params->data[i].args[0] != NULL)
				free(params->data[i].args[0]);
			free(params->data[i].args);
		}
		if (params->data[i].redirection_node != NULL)
			free_list(&params->data[i].redirection_node);
		if (params->data[i].in_fd != 0)
			close(params->data[i].in_fd);
		if (params->data[i].out_fd != 0)
			close(params->data[i].out_fd);
		i++;
	}
	free(params->data);
	params->data = NULL;
}

void	free_list(t_token **head)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		if ((*head)->word != NULL)
			free_word_list(&(*head)->word);
		free(*head);
		*head = tmp;
	}
	*head = NULL;
}

void	free_word_list(t_word_type **head)
{
	t_word_type	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		if ((*head)->str != NULL)
			free((*head)->str);
		free (*head);
		*head = tmp;
	}
	*head = NULL;
}

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list->next;
		free(env_list->variable);
		free(env_list->value);
		free(env_list);
		env_list = tmp;
	}
}
