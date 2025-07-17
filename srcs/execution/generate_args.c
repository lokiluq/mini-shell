/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:39:29 by cbaey             #+#    #+#             */
/*   Updated: 2025/04/06 22:17:16 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	create_args(t_params *params)
{
	t_token	*head;
	int		i;
	int		j;

	i = 0;
	head = params->token_list;
	while (i < params->no_of_commands && head)
	{
		j = count_nbr_of_args(head);
		params->data[i].args = malloc(sizeof(char *) * (j + 1));
		params->data[i].args[j] = NULL;
		assign_pointer_to_args(&head, params->data[i].args);
		i++;
		if (head != NULL && head->type == PIPE)
			head = head->next;
	}
}

int	count_nbr_of_args(t_token *head)
{
	int	i;

	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == HEREDOC)
			head = head->next;
		else if (head->type >= WORD && head->type <= DQUOTE)
			i++;
		head = head->next;
	}
	return (i);
}

void	assign_pointer_to_args(t_token **head, char **args)
{
	int	i;

	i = 0;
	while (*head && (*head)->type != PIPE)
	{
		if ((*head)->type == HEREDOC)
			*head = (*head)->next;
		else if ((*head)->type >= WORD && (*head)->type <= DQUOTE)
		{
			if (i == 0)
				args[i] = ft_strdup((*head)->word->str);
			else
				args[i] = (*head)->word->str;
			i++;
		}
		*head = (*head)->next;
	}
}
