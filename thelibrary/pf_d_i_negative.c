/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_d_i_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 09:32:20 by mgould            #+#    #+#             */
/*   Updated: 2017/02/05 12:14:45 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stddef.h>
#include <wchar.h>

char	*d_i_negative_handler(char *value, intmax_t storage)
{
	int i;

	i = 0;
	if (storage < 0 && *value != '-')
	{
		while (value[i])
		{
			if (value[i] == '-')
				value[i] = '0';
			i++;
		}
		i = 0;
		while (value[i] == ' ')
			i++;
		if (value[i] == '0' || value[i] == '-')
			value[i] = '-';
		else
			value[i - 1] = '-';
	}
	return (value);
}
