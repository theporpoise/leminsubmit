/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 20:37:36 by mgould            #+#    #+#             */
/*   Updated: 2016/12/04 18:42:04 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;
	unsigned char	newc;

	i = 0;
	p1 = (unsigned char *)dst;
	p2 = (unsigned char *)src;
	newc = (unsigned char)c;
	while (i < n)
	{
		*(p1 + i) = *(p2 + i);
		i++;
		if (*(p1 + i - 1) == newc)
			return ((p1 + i));
	}
	return (NULL);
}
