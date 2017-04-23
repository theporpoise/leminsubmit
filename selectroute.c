/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selectroute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 09:04:58 by mgould            #+#    #+#             */
/*   Updated: 2017/04/23 09:12:38 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

void		routecount(t_game *game)
{
	int		i;
	t_path	**tmp;

	i = 0;
	tmp = game->routes;
	while (tmp[i])
	{
		i++;
	}
	game->rnbr = i;
}

static int	singleroutecap(t_path *path)
{
	int i;
	int j;

	j = 0;
	while (path)
	{
		i = 0;
		while ((path->path)[i] > -1)
		{
			if ((path->path)[i] != 1 && (path->path)[i] > 0)
				j++;
			i++;
		}
		path = path->nx;
	}
	return (j);
}

void		routecap(t_game *game)
{
	int		i;
	int		*ret;

	i = 0;
	ret = malloc(sizeof(int) * (game->rnbr + 1));
	while (i < game->rnbr)
	{
		ret[i] = singleroutecap((game->routes)[i]);
		i++;
	}
	ret[i] = -1;
	game->rcap = ret;
}

t_path		*selectroute(t_game *game)
{
	int i;

	i = 0;
	while ((game->nbr > game->rcap[i]))
	{
		if (game->rcap[i + 1] == -1)
			break ;
		i++;
	}
	return ((game->routes)[i]);
}
