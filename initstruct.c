/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstruct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:04:04 by mgould            #+#    #+#             */
/*   Updated: 2017/04/21 11:33:06 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

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
	game->rnbr = 0;
	game->rcap = NULL;
	return (game);
}

t_room	*makeroom(char *name, int x, int y)
{
	t_room		*room;
	static int	i;

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
	path->origin = path;
	path->nx = NULL;
	return (path);
}

t_path	**routearray(int capacity)
{
	int		i;
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

t_ant	*makeant(t_path *path)
{
	static int	i;
	t_ant		*ant;

	i += 1;
	ant = malloc(sizeof(t_ant));
	ant->nbr = i;
	ant->step = 2;
	ant->path = path->path;
	ant->nx = NULL;

	return (ant);
}














