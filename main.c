/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 18:30:33 by mgould            #+#    #+#             */
/*   Updated: 2017/04/20 12:37:27 by mgould           ###   ########.fr       */
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

int		overlap(t_game *game, t_path *path, int *two)
{
	int i;
	int j;

	if (!path)
		return (0);
	i = 0;
	j = 0;
	while (path)
	{
		printf("inside overlap while round:%d\n", j);
		i = 0;
		while ((path->path)[i] >= 0)
		{
			printf("path->pathi:%d, twoi:%d\n", (path->path)[i], two[i]);
			if ((game->end)->id == i)
				;
			else if ((game->start)->id == i)
				;
			else if (((path->path)[i] * two[i]) > 0)
			{
				printf("there is an overlap at position:%d\n", i);
				return (1);
			}
			i++;
		}
		j++;
		path = path->nx;
	}
	return (0);
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
	//tmp = path;
	if (i != (n + 1))
	{
		while(routes[n])
		{
			tmp = (routes[n])->nx;
			releasepath(routes[n]);
			routes[n] = tmp;
		}
		printf("DID NOT find enough paths:%d for route:%d\n", (i + 1), n);
		return (0);
	}
	return (1);
}

int		getrouten(t_path **routes, t_game *game, int n)
{
	int i;
	t_path *tmp;
	t_path *iter;
	//t_path *head;

	iter = game->path;
	tmp = NULL;
	//head = tmp;
	i = 0;

	while (i < (n + 1))
	{
		if (!iter)
			break ;
		else if (overlap(game, routes[n], (iter)->path))
		{
			printf("you triggered overlap\n");
			iter = iter->nx;
			continue;
		}
		else
		{
			tmp = copypath(iter);
			tmp->nx = routes[n];
			routes[n] = tmp;
			iter = iter->nx;
		}
		i++;
	}
	//checking to see if enough paths in route
	if (!enoughpaths(routes, n))
		return (0);
	/*
	i = 0;
	tmp = routes[n];
	while (tmp)
	{
		i++;
		tmp = tmp->nx;
	}
	if (i != (n + 1))
	{
		while(routes[n])
		{
			tmp = (routes[n])->nx;
			releasepath(routes[n]);
			routes[n] = tmp;
		}
		printf("DID NOT find enough paths:%d for route:%d\n", (i + 1), n);
		return (0);
	}
	*/
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
		if (!getrouten((game->routes), game, i))
		{
			printf("breaking early bc not enough paths\n");
			//recursively call getrouten with next one in batch.
			//pass in next path?, but start checking at beginning of list?
			//terminate if you hit the end?
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
	debug_allpaths(game);
	if (!game->path)
		return (0);
	networkcapacity(game);
	//here is the error
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
