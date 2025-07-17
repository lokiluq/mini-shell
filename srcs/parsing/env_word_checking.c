/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_word_checking.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:51:03 by cbaey             #+#    #+#             */
/*   Updated: 2024/10/04 12:37:38 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_env_in_word(t_token **head, t_env *env, int exit_code)
{
	t_token	*current;
	t_token	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (current->word != NULL && (!prev || (prev && prev->type != HEREDOC)))
		{
			insertion_of_sublist(&(current->word), env, exit_code);
			if (!current->word)
			{
				move_token_ptr(head, &current, prev);
				continue ;
			}
		}
		prev = current;
		current = current->next;
	}
}

void	move_token_ptr(t_token **head, t_token **current, t_token *prev)
{
	t_token	*next_ptr;

	next_ptr = (*current)->next;
	if (!prev)
		*head = next_ptr;
	else
		prev->next = next_ptr;
	free(*current);
	*current = next_ptr;
}

void	insertion_of_sublist(t_word_type **head, t_env *env, int exit_code)
{
	t_word_type	*current;
	t_word_type	*new_head;
	t_word_type	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		new_head = NULL;
		if ((current->type == WORD || current->type == DQUOTE)
			&& expansion_of_dollar_sign(current->str,
				&new_head, env, exit_code))
			delete_and_insert(head, new_head, &current, &prev);
		else
		{	
			prev = current;
			current = current->next;
		}
	}
}

void	delete_and_insert(t_word_type **head, t_word_type *new_head,
		t_word_type **current, t_word_type **prev)
{
	t_word_type	*next;

	next = (*current)->next;
	if (!*prev)
		*head = new_head;
	else
		(*prev)->next = new_head;
	if (new_head)
	{
		*prev = last_word_node(new_head);
		(*prev)->next = (*current)->next;
	}
	free((*current)->str);
	free(*current);
	*current = next;
}

// 0 for start, 1 for pointer, 2 for tmp
bool	expansion_of_dollar_sign(char *str,
		t_word_type **head, t_env *head_env, int exit_code)
{
	char	*ptrs[3];
	int		result;
	bool	valid_expansion;

	ptrs[0] = str;
	ptrs[2] = str;
	valid_expansion = false;
	while (1)
	{
		ptrs[1] = ft_strchr(ptrs[2], '$');
		result = find_dollar_sign(head, ptrs[1], &ptrs[2], ptrs[0]);
		if (result == -1)
			break ;
		else if (result == 0)
			continue ;
		else if (result == 1)
			valid_expansion = expansion_of_dollar_sign_2
				(head, head_env, exit_code, ptrs);
		else if (result == -2)
			return (true);
	}
	return (valid_expansion);
}
