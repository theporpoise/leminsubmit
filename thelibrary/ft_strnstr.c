/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 18:47:29 by mgould            #+#    #+#             */
/*   Updated: 2016/12/05 18:56:50 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	ptr = (char *)big;
	if (!(little[i]))
		return (ptr);
	while (ptr[i] && (i < len))
	{
		j = 0;
		while ((ptr[i + j] == little[j]) && ptr[i + j] && (j + i) < len)
		{
			j++;
		}
		if (!little[j])
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}
