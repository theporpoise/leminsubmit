/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 15:23:45 by mgould            #+#    #+#             */
/*   Updated: 2016/12/04 18:49:25 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = 0;
	while (i < len)
	{
		if (src[i] && flag == 0)
			dst[i] = src[i];
		else
		{
			flag = 1;
			dst[i] = '\0';
		}
		i++;
	}
	return (dst);
}
