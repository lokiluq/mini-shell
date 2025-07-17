/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:39:06 by lnul-hak          #+#    #+#             */
/*   Updated: 2024/10/04 14:56:02 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_all(t_params *params)
{
	int		i;
	int		pipes[4];
	pid_t	pid;

	if (parent_process(params, pipes))
		return ;
	i = -1;
	while (++i < params->no_of_commands)
	{
		if (i < (params->no_of_commands - 1))
			pipe(pipes);
		pid = fork();
		if (pid == 0)
			child_process(params, i, pipes + 2, pipes);
		else
			pipe_handling(params, i, pipes + 2, pipes);
	}
	waitpid(pid, &params->exit_code, 0);
	if (WIFEXITED(params->exit_code))
		params->exit_code = WEXITSTATUS(params->exit_code);
	else if (WIFSIGNALED(params->exit_code))
		params->exit_code = WTERMSIG(params->exit_code) + 128;
	i = -1;
	while (++i < params->no_of_commands - 1)
		wait(NULL);
}

char	**conv_env_list(t_env	*env)
{
	char	**res;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	res = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		tmp = (t_env *)ft_strjoin(env->variable, "=");
		res[i] = ft_strjoin((char *)tmp, env->value);
		free(tmp);
		i++;
		env = env->next;
	}	
	res[i] = NULL;
	return (res);
}

void	free_array(char **env_list)
{
	int	i;

	i = 0;
	while (env_list[i])
	{
		free(env_list[i]);
		i++;
	}
	free(env_list);
}

void	pipe_handling(t_params *params, int i, int *old_pipe, int *new_pipe)
{
	if (i != 0)
	{
		close(old_pipe[0]);
		close(old_pipe[1]);
	}
	if (i != (params->no_of_commands - 1))
	{
		old_pipe[0] = new_pipe[0];
		old_pipe[1] = new_pipe[1];
	}
}
