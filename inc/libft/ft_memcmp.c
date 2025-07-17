/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:32:52 by cbaey             #+#    #+#             */
/*   Updated: 2023/10/03 18:05:47 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p;
	unsigned char	*q;

	p = (unsigned char *)s1;
	q = (unsigned char *)s2;
	if (s1 == s2)
		return (0);
	while (n > 0)
	{
		if (*p != *q)
			return (*p - *q);
		n--;
		p++;
		q++;
	}
	return (0);
}
/*
#include <string.h>
int	main(void)
{
	int	i = 0;
	i = ft_memcmp("abc", "abc", 2);
	printf("%d\n", i);
	printf("%d\n", ft_memcmp("abcdefghij", "abcdefgxyz", 7));
	printf("%d\n", memcmp("abcdefghij", "abcdefgxyz", 7));
	printf("%d\n", ft_memcmp("123456789", "123456788", 9));
	printf("%d\n", memcmp("123456789", "123456788", 9));
	printf("%d\n", ft_memcmp("abc123", "abcdef", 5));
	printf("%d\n", memcmp("abc123", "abcdef", 5));
	printf("%d\n", ft_memcmp("!@#$%", "!@#$%", 5));
	printf("%d\n", memcmp("!@#$%", "!@#$%", 5));

}*/
