/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 18:30:33 by mgould            #+#    #+#             */
/*   Updated: 2017/04/23 21:31:30 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

//TO DO
//check lemin grade sheet, norm, recheck grading sheet and test cases

int	freethemalloc(t_game **gamepointer)
{
	int i;
	t_game *game;
	t_ant	*ant;
	t_path	*ptmp;

	i = 0;
	game = *gamepointer;
	ant = game->ant;


	while((game->routes)[i])
	{
		while ((game->routes)[i])
		{
			ptmp = ((game->routes)[i])->nx;
			free(((game->routes)[i])->path);
			free((game->routes)[i]);
			(game->routes)[i] = ptmp;
		}
		i++;
	}
	free(game->routes);


	free(game->rcap);

	while (game->ant)
	{
		ant = (game->ant)->nx;
		free(game->ant);
		game->ant = ant;
	}


	free(game);
	return (0);
}

int main(void)
{
	t_game	*game;

	game = makegame();
	if (!parseinput(game))
	{
		return (freethemalloc(&game));
		//free everything
	}
	game->map = makemap(game);
	game->edge = makeedge(game);
	if (!routefinder(game))
	{
		printf("Error\nThere are no valid routes!\n");
		//free everything
		return (freethemalloc(&game));
		//return (0);
	}
	routecount(game);
	routecap(game);
	antmarch(game);
	//free everything
	//free(game);
	return (freethemalloc(&game));
	//return (0);
}
