/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_word_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:15:56 by cbaey             #+#    #+#             */
/*   Updated: 2024/10/01 15:15:43 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_word_type	*create_word_node(char *str, int type)
{
	t_word_type	*node;

	node = malloc(sizeof(t_word_type));
	node->str = str;
	node->type = type;
	node->str_len = ft_strlen(str);
	node->next = NULL;
	return (node);
}

void	append_word_list(t_word_type **head, char *str, int type)
{
	t_word_type	*node;

	node = create_word_node(str, type);
	if (!(*head))
		*head = node;
	else
		last_word_node(*head)->next = node;
}

t_word_type	*last_word_node(t_word_type *head)
{
	while (head->next)
		head = head->next;
	return (head);
}
