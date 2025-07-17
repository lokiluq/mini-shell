/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:40:15 by cbaey             #+#    #+#             */
/*   Updated: 2023/09/21 17:15:49 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned char	*dst;

	dst = str;
	while (len > 0)
	{
		*dst = (unsigned char) c;
		dst++;
		len--;
	}
	return (str);
}
/*
int	main(void)
{
	char	c[] = "hello";
	mem_set(c, 's', 2);
	printf("%s\n", c);
}*/
