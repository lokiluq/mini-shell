/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:48:33 by cbaey             #+#    #+#             */
/*   Updated: 2023/10/02 16:16:55 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr( const char *s, int c)
{
	while (*s)
	{
		if ((char)*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*c = "Hello";
	int	i = 101;

	printf("%s", strchr(c, i));
}*/
