/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:07:29 by cbaey             #+#    #+#             */
/*   Updated: 2023/09/25 18:17:32 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*csrc;
	char		*cdest;
	size_t		i;

	csrc = src;
	cdest = dst;
	i = 0;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dst);
}
/*
int	main(void)
{
	char csrc[] = "hello world";
	char cdest[] = "byebye";
	mem_cpy( cdest, csrc, 12);
	printf("%s", cdest);
}*/
