/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:28:59 by lnul-hak          #+#    #+#             */
/*   Updated: 2024/09/30 17:18:30 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_token **head, char *str)
{
	bool	first_word;

	first_word = true;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			find_quote(head, &str, &first_word, *str);
		else if (*str == '|')
		{
			first_word = append_list(head, NULL, PIPE);
			str++;
		}
		else if (ft_strncmp(str, ">>", 2) == 0)
		{
			first_word = append_list(head, NULL, APPEND);
			str += 2;
		}
		else
			parsing_2(head, &str, &first_word);
		if (*str == '\0')
			break ;
	}
}

void	parsing_2(t_token **head, char **str, bool *first_word)
{
	if (ft_strncmp(*str, "<<", 2) == 0)
	{
		*first_word = append_list(head, NULL, HEREDOC);
		*str += 2;
	}
	else if (**str == '>')
	{
		*first_word = append_list(head, NULL, TRUNCATE);
		(*str)++;
	}
	else if (**str == '<')
	{
		*first_word = append_list(head, NULL, IN);
		(*str)++;
	}
	else if (**str == ' ')
	{
		*first_word = true;
		(*str)++;
	}
	else
		unquoted_str(str, head, first_word);
}

void	unquoted_str(char **str, t_token **head, bool *first_word)
{
	char	*out;
	int		i;

	i = 0;
	while ((*str)[i] != ' ' && (*str)[i] != '\'' && (*str)[i] != '"'
		&& (*str)[i] != '<' && (*str)[i] != '>' && (*str)[i] != '|'
		&& (*str)[i])
		i++;
	out = malloc(sizeof(char) * i + 1);
	ft_strlcpy(out, *str, i + 1);
	out[i] = '\0';
	if (*first_word == true)
	{
		append_list(head, NULL, WORD);
		*first_word = false;
	}
	append_word_list(&(last_node(*head)->word), out, WORD);
	*str += i;
}

void	find_quote(t_token **head, char **str, bool *first_word, char quote)
{
	char	*new;
	int		type;
	int		i;

	i = 1;
	if (**str == '\'')
		type = SQUOTE;
	else
		type = DQUOTE;
	while ((*str)[i] && (*str)[i] != quote)
		i++;
	new = malloc(sizeof(char) * i);
	ft_strlcpy(new, *str + 1, i);
	new[i - 1] = '\0';
	if (*first_word == true)
	{
		append_list(head, NULL, type);
		*first_word = false;
	}
	append_word_list(&(last_node(*head)->word), new, type);
	if (*(*str + i) == '\0')
		*str += i;
	else
		*str += i + 1;
}
