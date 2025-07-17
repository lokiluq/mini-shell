/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:55:15 by cbaey             #+#    #+#             */
/*   Updated: 2024/10/04 16:38:07 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_spot;

void	signal_handling(int signum)
{
	g_spot = signum;
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	command_prompt(char *prompt, t_params *params, char *line,
		struct sigaction sa)
{
	while (1)
	{
		ft_memset(&sa, 0, sizeof(sa));
		sa.sa_handler = &signal_handling;
		sigaction(SIGINT, &sa, NULL);
		params->data = NULL;
		line = readline(prompt);
		if (g_spot != 0)
		{
			params->exit_code = g_spot + 128;
			g_spot = 0;
		}
		if (line)
		{
			if (!parse_all(params, line))
				continue ;
			exec_all(params);
			free_all(params);
		}
		else
			break ;
	}
}

bool	parse_all(t_params *params, char *line)
{
	if (*line)
		add_history(line);
	params->read_line = line;
	parsing(&params->token_list, line);
	check_env_in_word(&params->token_list, params->env_list, params->exit_code);
	if (!params->token_list)
		return (free_all(params), false);
	flatten_word_list(&params->token_list);
	if (syntax_check(params->token_list) == false)
	{
		printf("syntax error\n");
		return (free_all (params), false);
	}
	if (prep_for_heredoc(params) == 1)
		return (free_all (params), false);
	prep_for_redirect(params);
	create_args(params);
	return (true);
}
