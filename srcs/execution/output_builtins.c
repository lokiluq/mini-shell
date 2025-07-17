/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:04:41 by lnul-hak          #+#    #+#             */
/*   Updated: 2024/10/02 17:57:20 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_handler(t_params *params, int i)
{
	t_env	*tmp;

	(void)i;
	tmp = params->env_list;
	while (tmp)
	{
		printf("%s=%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
}

void	pwd_handler(t_params *params, int i)
{
	char	*working_directory;

	(void)params;
	(void)i;
	working_directory = getcwd(NULL, 1000);
	printf("%s\n", working_directory);
	free(working_directory);
}

char	*echo_utils(char *str, char *c)
{
	int	i;
	int	len;

	len = ft_strlen(c);
	while (*str)
	{
		i = 0;
		while (*str != c[i] && c[i])
			i++;
		if (i == len)
			return (str);
		str++;
	}
	return (NULL);
}

void	echo_handler(t_params *params, int i)
{
	bool	print_nl;
	int		j;

	j = 1;
	print_nl = true;
	if (params->data[i].args[1] == NULL)
		return ((void)printf("\n"));
	while (params->data[i].args[j]
		&& ft_strrchr(params->data[i].args[j], '-') == params->data[i].args[j]
		&& !(echo_utils(params->data[i].args[j], "-n"))
		&& ft_strlen(params->data[i].args[j]) > 1)
	{
		print_nl = false;
		j++;
	}
	while (params->data[i].args[j])
	{
		printf("%s", params->data[i].args[j]);
		if (params->data[i].args[j + 1] != NULL)
			printf(" ");
		j++;
	}
	if (print_nl == true)
		printf("\n");
}
