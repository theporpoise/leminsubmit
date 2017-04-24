/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 11:07:44 by mgould            #+#    #+#             */
/*   Updated: 2017/03/06 07:46:16 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	**ft_strsplit(char const *s, char c)
{
	int		i;
	char	**ar;
	char	*ptrs;

	if (!s)
		return (NULL);
	ptrs = (char *)s;
	if (!(ar = ((char **)malloc(sizeof(char*) * (ft_wc(ptrs, c) + 1)))))
		return (NULL);
	i = 0;
	while (*ptrs)
	{
		if (*ptrs == c)
		{
			ptrs++;
		}
		else
		{
			ar[i] = ft_make_word(ptrs, c);
			ptrs += (ft_strlen(ar[i]));
			i++;
		}
	}
	ar[i] = (NULL);
	return (ar);
}
