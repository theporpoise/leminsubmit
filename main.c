/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 18:30:33 by mgould            #+#    #+#             */
/*   Updated: 2017/04/23 10:06:25 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

//TO DO
//check lemin grade sheet, norm, recheck grading sheet and test cases

int	freethemalloc(t_game **gamepointer)
{
	t_game *game;

	game = *gamepointer;
	free(game);
	return (0);
}

int main(void)
{
	t_game	*game;

	game = makegame();
	if (!parseinput(game))
	{
		return (0);
		//free everything
	}
	game->map = makemap(game);
	game->edge = makeedge(game);
	if (!routefinder(game))
	{
		printf("Error\nThere are no valid routes!\n");
		//free everything
		return (0);
	}
	routecount(game);
	routecap(game);
	antmarch(game);
	//free everything
	free(game);
	return (0);
}
