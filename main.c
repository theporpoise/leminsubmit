/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 18:30:33 by mgould            #+#    #+#             */
/*   Updated: 2017/04/20 18:11:52 by mgould           ###   ########.fr       */
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
//int		*idup(int *path)
//check total moves vs. total nodes
//break if it doesn't work, figure out how to return
//break if route overlap
//

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
		//remove this side effect
		/*
		while(routes[n])
		{
			tmp = (routes[n])->nx;
			releasepath(routes[n]);
			routes[n] = tmp;
		}
		printf("DID NOT find enough paths:%d for route:%d\n", (i + 1), n);
		*/
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


int		getrouten(t_path **routes, t_game *game, int n, t_path *prev)
{
	int i;
	t_path *tmp;
	t_path *iter;
	t_path *recursetmp;

	if (!prev)
		return (0);
	//printf("now assigning iter\n");
	iter = (prev->origin)->nx;

	tmp = prev;
	routes[n] = tmp;
	//printf("in get route n\n");
	i = 0;
	while (i < n) //(n + 1))
	{
		if (!iter)
		{
		//	printf("four\n");
			break ;
		}
		else if (overlap(game, routes[n], iter))
		{
		//	printf("you triggered overlap\n");
			iter = iter->nx;
			continue;
		}
		else
		{
	//		printf("no overlap\n");
			tmp = copypath(iter);
			tmp->nx = routes[n];
			routes[n] = tmp;
			iter = iter->nx;
		}
	//	printf("five\n");
		i++;
	}

	//checking to see if enough paths in route
	if (!enoughpaths(routes, n))
	{
	//	return (0);

	//	printf("begin recursion\n");
		if (prev->nx)
		{
	//		printf("one\n");
			recursetmp = prev->nx;
			recursetmp->origin = (prev->origin);
			releasepath(prev);
			return (getrouten(routes, game, n, recursetmp));
		}
		else if (!(prev->nx) && (prev->origin)->nx)
		{
	//		printf("two\n");
			recursetmp = copypath((prev->origin)->nx);
			releasepath(prev);
			return (getrouten(routes, game, n, recursetmp));
		}
		else
		{
			releasepath(prev);
			routes[n] = NULL;
	//		printf("hit the base case, there is no better combo\n");
			return (0);
		}
	}
//	printf("seven\n");
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
			printf("breaking early bc not enough paths\n");
			break ;
		}
//		printf("outside while\n");
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
	//debug_allpaths(game);
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

	//FUNCTION THAT SOLVES IT

	if (!routefinder(game))
	{
		printf("there are no valid routes!\n");
	}

	//cleanup
	free(game);
	return (0);
}





























	//find shortest path
	//get routes
	//make ants
	//calcualte routs + paths and print ant-walk function

	//DEBUG
	//debug_game(game, game->map, game->edge);

	//CLEANUP
	//create function that cleans up the game, everything is in the game
	//OR cleanup function can be a return value :-).
