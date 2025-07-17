/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:29:01 by lnul-hak          #+#    #+#             */
/*   Updated: 2024/10/02 18:59:49 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	open_file_failure(t_params *params, t_token *tmp,
		int *old_pipe, int *new_pipe)
{
	perror(tmp->next->word->str);
	free_all(params);
	if (!old_pipe && !new_pipe)
		return ((void)(params->exit_code = 1));
	free_env_list(params->env_list);
	if (old_pipe[0] != 0)
	{
		close(old_pipe[1]);
		close(old_pipe[0]);
	}
	if (new_pipe[0] != 0)
	{
		close(new_pipe[0]);
		close(new_pipe[1]);
	}
	exit(1);
}

static int	open_in_fd(t_token *tmp, t_params *params, int i, bool heredoc)
{
	int	fd;

	fd = 0;
	fd = open(tmp->next->word->str, O_RDONLY);
	if (heredoc == true && fd != -1)
		close(fd);
	else
	{
		if (params->data[i].in_fd != 0)
			close(params->data[i].in_fd);
		if (fd != -1)
			params->data[i].in_fd = fd;
	}
	return (fd);
}

void	open_fd(t_params *params, int i, int *old_pipe, int *new_pipe)
{
	t_token	*tmp;
	bool	heredoc;
	int		fd;

	heredoc = false;
	tmp = params->data[i].redirection_node;
	if (params->data[i].in_fd != 0)
		heredoc = true;
	while (tmp)
	{
		if (tmp->type == IN)
			fd = open_in_fd(tmp, params, i, heredoc);
		else
			fd = open_out_fd(tmp, params, i);
		if (fd == -1)
			open_file_failure(params, tmp, old_pipe, new_pipe);
		tmp = tmp->next->next;
	}
}

int	open_out_fd(t_token *tmp, t_params *params, int i)
{
	int	fd;

	fd = 0;
	if (tmp->type == TRUNCATE)
	{
		fd = open(tmp->next->word->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (params->data[i].out_fd != 0)
		{
			close(params->data[i].out_fd);
			params->data[i].out_fd = 0;
		}
	}
	else if (tmp->type == APPEND)
	{
		fd = open(tmp->next->word->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (params->data[i].out_fd != 0)
		{
			close(params->data[i].out_fd);
			params->data[i].out_fd = 0;
		}
	}
	if (fd != -1)
		params->data[i].out_fd = fd;
	return (fd);
}
