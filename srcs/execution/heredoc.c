/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:24:32 by cbaey             #+#    #+#             */
/*   Updated: 2024/10/04 12:27:49 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_heredoc(int signum);

static bool	find_heredoc(t_params *params, t_token *tmp)
{
	int	i;

	i = 0;
	while (tmp)
	{	
		if (tmp->type == PIPE)
			i++;
		else if (tmp->type == HEREDOC)
		{	
			if (params->data[i].in_fd != 0)
				close(params->data[i].in_fd);
			if (exec_heredoc(&tmp, i, params) == 1)
				return (1);
		}
		else if (tmp-> type == IN && params->data[i].in_fd != 0)
		{
			close(params->data[i].in_fd);
			params->data[i].in_fd = 0;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	prep_for_heredoc(t_params *params)
{
	int				pipes;
	t_child_data	*arr;

	pipes = pipe_counter(params->token_list);
	arr = malloc(sizeof(t_child_data) * (pipes + 1));
	ft_memset(arr, 0, sizeof(t_child_data) * (pipes + 1));
	params->data = arr;
	params->no_of_commands = pipes + 1;
	return (find_heredoc(params, params->token_list));
}

static bool	heredoc_loop(t_params *params,
	int *pipe_fd, char *delimiter, int len)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (g_spot != 0)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			params->exit_code = g_spot + 128;
			g_spot = 0;
			return (false);
		}
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, len + 1) == '\n')
		{		
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	return (true);
}

int	exec_heredoc(t_token **head, int idx, t_params	*params)
{
	struct sigaction	sa;
	int					pipe_fd[2];

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &signal_heredoc;
	sigaction(SIGINT, &sa, NULL);
	if (pipe(pipe_fd) == -1)
		perror("pipe");
	*head = (*head)->next;
	if (!heredoc_loop(params, pipe_fd,
			(*head)->word->str, (*head)->word->str_len))
		return (1);
	close(pipe_fd[1]);
	params->data[idx].in_fd = pipe_fd[0];
	return (0);
}

int	pipe_counter(t_token *head)
{
	int	count;

	count = 0;
	while (head)
	{
		if (head->type == PIPE)
			count++;
		head = head->next;
	}
	return (count);
}
