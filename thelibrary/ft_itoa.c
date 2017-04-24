/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 11:38:25 by mgould            #+#    #+#             */
/*   Updated: 2016/12/05 20:47:11 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_itoa(int n)
{
	int			len;
	long		copy;
	char		*num;

	len = 0;
	num = NULL;
	copy = n;
	if (n == 0)
	{
		if ((num = ft_getz(num)))
			return (num);
		else
			return (NULL);
	}
	if (copy < 0)
		len++;
	while (copy != 0)
	{
		len++;
		copy = copy / 10;
	}
	if (!(num = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_mnbr(num, len, n);
	return (num);
}
