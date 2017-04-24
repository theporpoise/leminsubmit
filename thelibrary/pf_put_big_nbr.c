/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_big_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 07:03:44 by mgould            #+#    #+#             */
/*   Updated: 2017/01/26 12:05:06 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <limits.h>
#include <stdint.h>
#include "libft.h"

void	pf_put_big_nbr(intmax_t n)
{
	intmax_t	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
	{
		pf_put_big_nbr(nb / 10);
		pf_put_big_nbr(nb % 10);
	}
	else
	{
		ft_putchar(nb + '0');
	}
}
