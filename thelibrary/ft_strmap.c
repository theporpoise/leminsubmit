/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 16:07:36 by mgould            #+#    #+#             */
/*   Updated: 2016/12/04 18:48:29 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*copy;
	int		i;

	i = 0;
	if (!s || !f)
		return (NULL);
	copy = ft_strdup(s);
	if (!copy)
		return (NULL);
	while (copy[i])
	{
		copy[i] = f(copy[i]);
		i++;
	}
	return (copy);
}
