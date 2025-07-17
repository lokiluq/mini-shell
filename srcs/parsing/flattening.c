/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flattening.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:32:34 by cbaey             #+#    #+#             */
/*   Updated: 2024/09/30 16:19:31 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flatten_word_list(t_token **head)
{
	char	*old_str_ptr;
	t_token	*ptr;

	ptr = *head;
	while (ptr)
	{
		if (ptr->word != NULL && ptr->word->next != NULL)
		{
			old_str_ptr = ptr->word->str;
			ptr->word->str = entire_word_buffer(ptr->word);
			free(old_str_ptr);
			free_word_list(&(ptr->word->next));
			ptr->word->str_len = ft_strlen(ptr->word->str);
		}
		ptr = ptr->next;
	}
}

char	*entire_word_buffer(t_word_type *word_node)
{
	char	*buffer;
	int		i;
	int		len;

	i = 0;
	len = length_of_entire_word(word_node);
	buffer = malloc(sizeof(char) * len + 1);
	while (word_node)
	{
		ft_strlcpy(buffer + i, word_node->str, word_node->str_len + 1);
		i += word_node->str_len;
		word_node = word_node->next;
	}
	buffer[len] = '\0';
	return (buffer);
}

int	length_of_entire_word(t_word_type *word_node)
{
	int	total_len;

	total_len = 0;
	while (word_node)
	{
		total_len += word_node->str_len;
		word_node = word_node->next;
	}
	return (total_len);
}
