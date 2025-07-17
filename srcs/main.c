/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:08:30 by cbaey             #+#    #+#             */
/*   Updated: 2024/10/01 19:51:54 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{	
	t_params	params;

	(void)argc;
	(void)argv;
	ft_memset(&params, 0, sizeof(params));
	params.env_list = init_env_list(env);
	params.exit_code = 0;
	g_spot = 0;
	signal(SIGQUIT, SIG_IGN);
	command_prompt(PROMPT, &params, NULL, (struct sigaction){});
	free_env_list(params.env_list);
	return (0);
}

void	signal_heredoc(int signum)
{
	g_spot = signum;
	write(STDIN_FILENO, "\n", 1);
}
