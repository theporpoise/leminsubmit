/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 18:20:53 by mgould            #+#    #+#             */
/*   Updated: 2016/11/30 19:10:34 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int			i;
	const char	*ps;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			ps = &s[i];
			return ((char *)ps);
		}
		i++;
	}
	if (c == '\0' && s[i] == '\0')
	{
		ps = &s[i];
		return ((char *)ps);
	}
	return (NULL);
}
