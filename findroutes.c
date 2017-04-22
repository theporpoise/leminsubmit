/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findroutes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 20:08:38 by mgould            #+#    #+#             */
/*   Updated: 2017/04/21 21:24:39 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

static int	overlap(t_game *game, t_path *path, t_path *two)
{
	int i;

	if (!path)
		return (0);
	if (two->moves == 1)
		return (1);
	i = 0;
	while (path)
	{
		i = 0;
		while ((path->path)[i] >= 0)
		{
			if ((game->end)->id == i)
				;
			else if ((game->start)->id == i)
				;
			else if (((path->path)[i] * (two->path)[i]) > 0)
				return (1);
			i++;
		}
		path = path->nx;
	}
	return (0);
}

static void	looptosolution(t_path **routes, t_game *game, int n, t_path *prev)
{
	t_path *tmp;
	t_path *iter;

	iter = (prev->origin)->nx;
	tmp = prev;
	routes[n] = tmp;
	while (!enoughpaths(routes, n) && iter)
	{
		if (!overlap(game, routes[n], iter))
		{
			tmp = copypath(iter);
			tmp->nx = routes[n];
			routes[n] = tmp;
		}
		iter = iter->nx;
	}
}

static int	getrouten(t_path **routes, t_game *game, int n, t_path *prev)
{
	t_path		*rtmp;
	static int	i;

	if (!prev || (++i > 100000))
		return (0);
	looptosolution(routes, game, n, prev);
	if (!enoughpaths(routes, n))
	{
		if (!(prev->nx) && !((prev->origin)->nx) && (rtmp = NULL))
			routes[n] = NULL;
		else if (prev->nx && (rtmp = prev->nx))
			rtmp->origin = (prev->origin);
		else if ((prev->origin)->nx)
			rtmp = copypath((prev->origin)->nx);
		releasepath(prev);
		return (getrouten(routes, game, n, rtmp));
	}
	return (1);
}

static void	getroutes(t_game *game)
{
	int n;
	int i;

	i = 0;
	n = game->cap;
	game->routes = routearray(n);
	while (i < n)
	{
		if (!getrouten((game->routes), game, i, copypath(game->path)))
		{
			(game->routes)[i] = NULL;
		//	printf("breaking early bc not enough paths\n");
			break ;
		}
		i++;
	}
}

int			routefinder(t_game *game)
{
	int *path;

	path = malloc(sizeof(int) * (((game->rmlst)->id) + 2));
	ft_memset(path, 0, sizeof(path));
	path[((game->rmlst)->id) + 1] = -1;
	path[(game->start)->id] = (path[((game->rmlst)->id) + 1] * -1);
	allvalidpaths(game, (game->end)->id, path, (game->start)->id);
	if (!game->path)
		return (0);
	networkcapacity(game);
	getroutes(game);
	return (1);
}
