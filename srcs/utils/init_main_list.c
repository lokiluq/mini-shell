/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:22:42 by lnul-hak          #+#    #+#             */
/*   Updated: 2024/10/01 15:12:41 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_nodes(t_word_type *str, int type)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->word = str;
	node->type = type;
	node->next = NULL;
	return (node);
}

bool	append_list(t_token **head, t_word_type *word, int type)
{
	t_token	*node;

	node = init_nodes(word, type);
	if (!(*head))
		*head = node;
	else
		last_node(*head)->next = node;
	return (true);
}

t_token	*last_node(t_token *head)
{
	while (head->next)
		head = head->next;
	return (head);
}
