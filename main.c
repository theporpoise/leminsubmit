/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 18:30:33 by mgould            #+#    #+#             */
/*   Updated: 2017/04/20 21:00:05 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

	//MARCH ANTS
	//creat ant stack
	//create helper room lookup
	//route chooser
	//	->capacity per route
	//print function runs through ant stack

	//DEBUG
	//debug_game(game, game->map, game->edge);

	//CLEANUP
	//create function that cleans up the game struct
	//OR cleanup function can be a return value :-).

	//MEMORY
	//gonna have to chase this one down with Valgrind on the splitwords fncs

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
	//ant = game->nbr; while ants, create ant stack with ant name.
	//ant struct
	//		->carries a map and their name
	//		->prints L(antnumber)-(destinationname)
	//routevalues ->create integer array? will need to look these up. . .
	//

	//cleanup
	free(game);
	return (0);
}







