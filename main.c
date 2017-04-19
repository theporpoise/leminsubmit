/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 18:30:33 by mgould            #+#    #+#             */
/*   Updated: 2017/04/19 12:59:26 by mgould           ###   ########.fr       */
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



t_path	*copypath(t_path *path)
{
	t_path *ret;

	ret = malloc(sizeof(t_path));
	ret->path = idup(path->path);
	ret->moves = path->moves;
	ret->nx = NULL;

	return (ret);
}

//check total moves vs. total nodes
//break if it doesn't work, figure out how to return
//break if route overlap
//
//functions to make:
//route overlap
//recursive iterator function that uses route overlap

//int	getpath(select path to add to route);

//if equal in length to n, then return
//if empty, choose the first route
//else recurse


//int		getrouten(t_path *routes, t_game *game, int n)
int		getrouten(t_path **routes, t_game *game, int n)
{
	int i;
	int ret;
	t_path *tmp;

	tmp = NULL;
	ret = 1;
	i = 0;

//	routes = NULL;
//	game = NULL;
//	n = 1;




	while (i < (n + 1))
	{
		//select the correct route here, this is thinking
		tmp = copypath(game->path);
		//tmp->nx = routes;
		tmp->nx = routes[n];
		routes[n] = tmp;
		//routes = tmp;
		i++;
	}


	return (ret);
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
		getrouten((game->routes), game, i);
		//getrouten((game->routes)[i], game, i);
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
	printf("AFTER GETROUTES, GOT %d ROUTES\n", game->cap);
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
