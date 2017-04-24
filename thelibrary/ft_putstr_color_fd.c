/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 14:01:59 by mgould            #+#    #+#             */
/*   Updated: 2017/02/20 14:22:46 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#define CRED "\x1B[31m"
#define CGRN "\x1B[32m"
#define CYEL "\x1B[33m"
#define RESET "\033[0m"

void	ft_putstr_color_fd(char *str, int color, int fd)
{
	char *colors[] =
	{RESET, CRED, CGRN, CYEL};

	ft_putstr_fd(colors[color], fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(RESET, fd);
}
