/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 19:13:57 by mgould            #+#    #+#             */
/*   Updated: 2016/12/06 14:32:58 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0 && (!(s1[0]) || !(s2[0])))
		return (0);
	while (*s1 && *s2 && (*s1 == *s2) && (n > 0))
	{
		s1++;
		s2++;
		n--;
	}
	if (*(s1 - 1) == *(s2 - 1) && n == 0)
		return (0);
	else if (*s1 == *s2)
		return (0);
	else if (*s1 == '\0' && *s2 != '\0')
		return (*(unsigned char*)s1 - *(unsigned char*)s2);
	else if (*s2 == '\0' && *s1 != '\0')
		return (*(unsigned char*)s1 - *(unsigned char*)s2);
	return (*(unsigned char*)s1 - *(unsigned char*)s2);
}
