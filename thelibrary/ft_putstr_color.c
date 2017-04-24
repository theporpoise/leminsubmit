/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 14:01:59 by mgould            #+#    #+#             */
/*   Updated: 2017/02/20 14:18:27 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#define CRED "\x1B[31m"
#define CGRN "\x1B[32m"
#define CYEL "\x1B[33m"
#define RESET "\033[0m"

void	ft_putstr_color(char *str, int color)
{
	char *colors[] =
	{RESET, CRED, CGRN, CYEL};

	ft_putstr(colors[color]);
	ft_putstr(str);
	ft_putstr(RESET);
}
