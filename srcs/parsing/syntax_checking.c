/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:50:41 by cbaey             #+#    #+#             */
/*   Updated: 2024/09/30 16:25:11 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	syntax_check(t_token *head)
{
	t_token	*prev;

	prev = NULL;
	while (head)
	{
		if (head->type == PIPE && (prev == NULL
				|| head->next == NULL || head->next->type == PIPE))
			return (false);
		else if ((head->type >= IN && head->type <= HEREDOC)
			&& (head->next == NULL || (head->next->type >= IN
					&& head->next->type <= PIPE)))
			return (false);
		prev = head;
		head = head->next;
	}
	return (true);
}
