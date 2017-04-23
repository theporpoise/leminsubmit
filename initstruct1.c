/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstruct1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 08:48:25 by mgould            #+#    #+#             */
/*   Updated: 2017/04/23 08:51:18 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

t_ant	*makeant(t_path *path)
{
	static int	i;
	t_ant		*ant;

	i += 1;
	ant = malloc(sizeof(t_ant));
	ant->nbr = i;
	ant->step = 2;
	ant->path = path->path;
	ant->nx = NULL;
	ant->donezo = 0;
	return (ant);
}
