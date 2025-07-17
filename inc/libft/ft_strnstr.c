/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:57:09 by cbaey             #+#    #+#             */
/*   Updated: 2023/09/25 18:26:16 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*c;
	const char	*v;
	size_t		litlen;

	litlen = 0;
	while (little[litlen] != '\0')
		litlen++;
	if (litlen == 0)
		return ((char *)big);
	while (*big != '\0' && len >= litlen)
	{
		c = big;
		v = little;
		while (*v != '\0' && *c == *v)
		{
			c++;
			v++;
		}
		if (*v == '\0')
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
/*
int	main(void)
{
	const char	*c = "Helloworld";
	const char	*v = "wo";

	printf("%s", strnstr(c, v, sizeof(v)));
}*/
