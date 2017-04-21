/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 18:30:33 by mgould            #+#    #+#             */
/*   Updated: 2017/04/21 11:36:31 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

	//MARCH ANTS
	//creat ant stack
	//create helper room lookup
	//route chooser
	//	->capacity per route
	//print function runs through ant stack

	//MARCH THE ANTS
	//ant = game->nbr; while ants, create ant stack with ant name.
	//ant struct
	//		->carries a map and their name
	//		->prints L(antnumber)-(destinationname)
	//routevalues ->create integer array? will need to look these up. . .

	//DEBUG
	//debug_game(game, game->map, game->edge);

	//CLEANUP
	//create function that cleans up the game struct
	//OR cleanup function can be a return value :-).

	//MEMORY
	//gonna have to chase this one down with Valgrind on the splitwords fncs

void	routecount(t_game *game)
{
	int 	i;
	t_path	**tmp;

	i = 0;
	tmp = game->routes;
	while (tmp[i])
	{
		i++;
	}
	game->rnbr = i;
}

int		singleroutecap(t_path *path)
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

void	routecap(t_game *game)
{
	int		i;
	int		*ret;

	i = 0;
	ret = malloc(sizeof(int) * (game->rnbr + 1));
	while (i < game->rnbr)
	{
		ret[i] = singleroutecap((game->routes)[i]);
		printf("\nroute %d with throughput %d cap is: %d\n", i, i+1, ret[i]);
		i++;
	}
	ret[i] = -1;
	game->rcap = ret;
}

t_path	*selectroute(t_game *game)
{
	int i;

	i = 0;
	while ((game->nbr > game->rcap[i])) // && game->rcap[i] != -1)
	{
		if (game->rcap[i + 1] == -1)
			break ;
		i++;
	}
	return ((game->routes)[i]);
}

void	printants(t_ant *ant)
{
	t_ant *tmp;

	tmp = ant;
	printf("PRINTING ANTS\n");
	while (tmp)
	{
		printf("ant number:%d, step is %d ant route is", tmp->nbr, tmp->step);
		debug_intarray(tmp->path);
		tmp = tmp->nx;
	}
}

void	antmarch(t_game *game)
{
	int i;
	t_path	*route;
	t_ant	*nextant;

	i = 0;
	while (game->nbr)
	{
		i++;
		printf("\n%d iter of ants made\n", i);
		route = selectroute(game);
		debug_pathsinroute(route);
		while(route)
		{
			nextant = makeant(route);
			route = route->nx;

			nextant->nx = game->ant;
			game->ant = nextant;
			game->nbr -= 1;
		}
		printants(game->ant);
		printf("end of while\n");
		//march ants and update their int arrays
		//  ->will need a room lookup, id to name
		//  ->print out L(antname)-(roomname) for every ant on same row
		//  ->have to make sure printing out the right move;
		//print their marching orders
	}
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
	//route setup
	routecount(game);
	printf("\nROUTECOUNT is %d\n", game->rnbr);
	routecap(game);
	//
	antmarch(game);


	//cleanup
	free(game);
	return (0);
}







