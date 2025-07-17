/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:34:00 by lnul-hak          #+#    #+#             */
/*   Updated: 2024/10/04 14:55:41 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parent_process(t_params *params, int *pipe)
{	
	int	built_in;

	ft_memset(pipe, 0, sizeof(int) * 4);
	signal(SIGINT, SIG_IGN);
	if (!params->data[0].args)
		return (false);
	built_in = find_built_in(params->data[0].args[0]);
	if (built_in >= 3 && built_in <= 6 && params->no_of_commands == 1)
	{
		open_fd(params, 0, NULL, NULL);
		if (!params->data)
			return (true);
		exec_builtin(params, 0, built_in);
		free_all(params);
		return (true);
	}
	return (false);
}

static void	execve_error(t_params *params, int i)
{
	DIR	*dir;

	dir = opendir(params->data[i].args[0]);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (dir)
	{
		params->exit_code = 126;
		printf("%s: Is a directory\n", params->data[i].args[0]);
		closedir(dir);
	}
	else if (access(params->data[i].args[0], F_OK) == 0
		&& access(params->data[i].args[0], X_OK) == -1)
	{
		perror(params->data[i].args[0]);
		params->exit_code = 126;
	}
	else
	{
		params->exit_code = 127;
		printf("%s: command not found\n",
			params->data[i].args[0]);
	}
}

void	exec_nonbuiltin(t_params *params, int i)
{
	char	**env_list;

	find_command_path(params, i);
	env_list = conv_env_list(params->env_list);
	execve(params->data[i].args[0],
		params->data[i].args, env_list);
	execve_error(params, i);
	free_array(env_list);
}

static void	close_unused_heredoc_fds(t_params *params, int i)
{
	int	j;

	j = 0;
	while (j < params->no_of_commands)
	{	
		if (j != i && params->data[j].in_fd != 0)
		{
			close(params->data[j].in_fd);
			params->data[j].in_fd = 0;
		}
		j++;
	}
}

void	child_process(t_params *params, int i, int *old_pipe, int *new_pipe)
{
	int	built_in;

	params->exit_code = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close_unused_heredoc_fds(params, i);
	open_fd(params, i, old_pipe, new_pipe);
	redirection(params, i, old_pipe, new_pipe);
	if (params->data[i].args && params->data[i].args[0])
	{
		built_in = find_built_in(params->data[i].args[0]);
		if (built_in < 7)
			exec_builtin(params, i, built_in);
		else
			exec_nonbuiltin(params, i);
	}
	free_all(params);
	free_env_list(params->env_list);
	exit (params->exit_code);
}
