/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstruct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:04:04 by mgould            #+#    #+#             */
/*   Updated: 2017/04/20 16:45:15 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem-in.h>

t_game	*makegame(void)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	game->nbr = 0;
	game->end = NULL;
	game->start = NULL;
	game->rmlst = NULL;
	game->lnlst = NULL;
	game->map = NULL;
	game->edge = NULL;
	game->cap = 0;
	game->path = NULL;
	game->routes = NULL;

	return (game);

}

t_room	*makeroom(char *name, int x, int y)
{
	t_room *room;
	static int i;

	room = malloc(sizeof(t_room));
	room->nm = name;
	room->id = i;
	room->x = x;
	room->y = y;
	room->nx = NULL;

	i++;
	return (room);
}


t_lnk	*makelnk(char *one, char *two)
{
	t_lnk	*lnk;

	lnk = malloc(sizeof(t_lnk));
	lnk->a = one;
	lnk->b = two;
	lnk->x = -1;
	lnk->y = -1;
	lnk->nx = NULL;

	return (lnk);
}

t_path	*makepath(int *array, int moves)
{
	t_path	*path;

	path = malloc(sizeof(t_path));
	path->path = array;
	path->moves = moves;
	path->origin = path; //path
	path->nx = NULL;

	return (path);
}


t_path	**routearray(int capacity)
{
	int i;
	t_path	**routes;

	i = 0;
	routes = malloc(sizeof(t_path *) * (capacity + 1));
	while (i < capacity)
	{
		routes[i] = NULL;
		i++;
	}
	routes[capacity] = NULL;
	return (routes);
}
