/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 19:45:12 by mgould            #+#    #+#             */
/*   Updated: 2016/12/05 19:45:31 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

int	ft_wc(char *s, char c)
{
	int	i;
	int flag;
	int	words;

	i = 0;
	flag = 0;
	words = 0;
	while (s[i])
	{
		if ((s[i] != c) && flag == 0)
		{
			flag = 1;
			words += 1;
		}
		else if (s[i] == c)
		{
			flag = 0;
		}
		i++;
	}
	return (words);
}
