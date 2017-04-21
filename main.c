/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 18:30:33 by mgould            #+#    #+#             */
/*   Updated: 2017/04/20 19:46:12 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <lem-in.h>


/*
** FINDING ROUTES
*/

t_path	*copypath(t_path *path)
{
	t_path *ret;

	ret = malloc(sizeof(t_path));
	ret->path = idup(path->path);
	ret->moves = path->moves;
	ret->origin = path; //path
	ret->nx = NULL;

	return (ret);
}

void	releasepath(t_path *path)
{
	if (!path)
		return;
	if (path->path)
		free(path->path);
	free(path);
}

int		enoughpaths(t_path **routes, int n)
{
	int i;
	t_path *tmp;

	tmp = routes[n];
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->nx;
	}
	if (i != (n + 1))
	{
		return (0);
	}
	return (1);
}

int		overlap(t_game *game, t_path *path, t_path *two)
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


void	looptosolution(t_path **routes, t_game *game, int n, t_path *prev)
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

int		getrouten(t_path **routes, t_game *game, int n, t_path *prev)
{
	t_path *rtmp;

	if (!prev)
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

void	getroutes(t_game *game)
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
			printf("breaking early bc not enough paths\n");
			break ;
		}
		i++;
	}
}

int	routefinder(t_game *game)
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
	printf("AFTER GETROUTES, MAX %d ROUTES\n", game->cap);
	debug_routes(game->routes, game);
	debug_edge(game->edge);
	return (1);
}


int main(void)
{
	t_game	*game;

	game = makegame();
	if (!parseinput(game))
	{
		return (0);
	}
	game->map = makemap(game);
	game->edge = makeedge(game);
	if (!routefinder(game))
	{
		printf("there are no valid routes!\n");
	}
	//MARCH THE ANTS

	//cleanup
	free(game);
	return (0);
}



























	//MARCH ANTS
	//make ants
	//calcualte routs + paths and print ant-walk function

	//DEBUG
	//debug_game(game, game->map, game->edge);

	//CLEANUP
	//create function that cleans up the game, everything is in the game
	//OR cleanup function can be a return value :-).
	//check memory
