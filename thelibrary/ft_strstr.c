/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 16:27:02 by mgould            #+#    #+#             */
/*   Updated: 2016/12/05 16:28:49 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	ptr = (char *)big;
	if (!(little[i]) && !(ptr[i]))
		return (ptr);
	while (ptr[i])
	{
		j = 0;
		while ((ptr[i + j] == little[j]) && ptr[i + j])
		{
			j++;
		}
		if (!little[j])
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}
