/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 21:03:04 by mgould            #+#    #+#             */
/*   Updated: 2016/12/05 16:14:38 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	int					dif;
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	i = 0;
	dif = 0;
	ptr1 = (const unsigned char *)s1;
	ptr2 = (const unsigned char *)s2;
	while (i < n)
	{
		dif = ptr1[i] - ptr2[i];
		if (dif != 0)
			return (dif);
		i++;
	}
	return (0);
}
