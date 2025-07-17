/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_word_checking_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:47:03 by cbaey             #+#    #+#             */
/*   Updated: 2024/10/03 17:10:06 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	expansion_of_dollar_sign_2(t_word_type **head,
		t_env *head_env, int exit_code, char **ptrs)
{
	int	i;

	i = 0;
	while (ptrs[0] + i != ptrs[1])
		i++;
	if (i != 0)
		create_word_token(i, head, ptrs[0]);
	ptrs[2] = ptrs[1] + 1;
	expand_env(&ptrs[2], head, head_env, exit_code);
	ptrs[0] = ptrs[2];
	return (true);
}

int	find_dollar_sign(t_word_type **head,
		char *pointer, char **tmp, char *start)
{	
	if (pointer == NULL)
	{
		if (*head != NULL && **tmp != '\0')
			return (append_word_list(head, ft_strdup(start), WORD), -2);
		return (-1);
	}
	if (*(pointer + 1) == '\0')
	{
		append_word_list(head, ft_strdup(start), WORD);
		return (-2);
	}
	if (*(pointer + 1) != '_' && ft_isalpha(*(pointer + 1)) == 0
		&& *(pointer + 1) != '?')
	{
		*tmp = pointer + 1;
		return (0);
	}
	return (1);
}

void	expand_env(char **tmp, t_word_type **head,
		t_env *head_env, int exit_code)
{
	int		i;
	char	*str;

	i = 0;
	if ((*tmp)[0] == '?')
		i = 1;
	else
		while ((*tmp)[i] && (ft_isalnum((*tmp)[i]) || (*tmp)[i] == '_'))
			i++;
	str = malloc(sizeof(char) * i + 1);
	ft_strlcpy(str, *tmp, i + 1);
	str = env_validation(str, head_env, exit_code, *tmp);
	if (str)
		append_word_list(head, str, ENV);
	*tmp += i;
}

void	create_word_token(int i, t_word_type **head, char *str)
{
	char	*out;

	out = NULL;
	out = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(out, str, i + 1);
	out[i] = '\0';
	append_word_list(head, out, WORD);
}

char	*env_validation(char *str, t_env *head, int exit_code, char *tmp)
{
	if (*tmp == '?')
	{
		free(str);
		return (ft_itoa(exit_code));
	}
	while (head)
	{
		if (ft_strncmp(str, head->variable, ft_strlen(head->variable) + 1) == 0)
		{	
			free(str);
			return (ft_strdup(head->value));
		}
		head = head->next;
	}
	free(str);
	return (NULL);
}
