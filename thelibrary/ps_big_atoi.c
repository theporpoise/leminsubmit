/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_big_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 09:06:43 by mgould            #+#    #+#             */
/*   Updated: 2017/02/24 09:28:21 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>

intmax_t	ps_big_atoi(const char *str)
{
	int			sign;
	intmax_t	number;

	number = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
			*str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
	{
		sign = sign * -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while ((*str > 47) && (*str < 58))
	{
		number *= 10;
		number += *str - '0';
		str++;
	}
	return (number * sign);
}
