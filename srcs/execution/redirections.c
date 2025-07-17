/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:00:05 by lnul-hak          #+#    #+#             */
/*   Updated: 2025/04/06 22:16:41 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prep_for_redirect(t_params *params)
{
	t_token	*head;
	t_token	*prev;
	int		i;

	i = 0;
	head = params->token_list;
	prev = NULL;
	while (head)
	{
		if (head->type == PIPE)
			i++;
		if (head->type >= IN && head->type <= APPEND)
		{
			extract_redirect(&head, prev, i, params);
			continue ;
		}
		prev = head;
		head = head->next;
	}
}

void	extract_redirect(t_token **head, t_token *prev, int i, t_params *params)
{
	if (!prev)
		params->token_list = (*head)->next->next;
	else
		prev->next = (*head)->next->next;
	if (!(params->data[i].redirection_node))
		params->data[i].redirection_node = *head;
	else
		last_node(params->data[i].redirection_node)->next = *head;
	(*head)->next->next = NULL;
	if (!prev)
		*head = params->token_list;
	else
		*head = prev->next;
}

void	redirection(t_params *params, int i, int *old_pipe, int *new_pipe)
{	
	if (old_pipe[0] != 0)
	{
		dup2(old_pipe[0], STDIN_FILENO);
		close(old_pipe[0]);
		close(old_pipe[1]);
	}	
	if (params->data[i].in_fd != 0)
	{
		dup2(params->data[i].in_fd, STDIN_FILENO);
		close(params->data[i].in_fd);
		params->data[i].in_fd = 0;
	}
	if (new_pipe[1] != 0 && i != (params->no_of_commands -1))
	{
		dup2(new_pipe[1], STDOUT_FILENO);
		close(new_pipe[0]);
		close(new_pipe[1]);
	}
	if (params->data[i].out_fd != 0)
	{
		dup2(params->data[i].out_fd, STDOUT_FILENO);
		close(params->data[i].out_fd);
		params->data[i].out_fd = 0;
	}
}
