/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displaymap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 09:55:06 by mgould            #+#    #+#             */
/*   Updated: 2017/04/19 09:57:27 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <lem-in.h>

int	xdim(t_game *game)
{
	t_room	*tmp;
	int xmax;
	int xmin;

	xmax = 0;
	xmin = 0;
	tmp = game->rmlst;
	while (tmp)
	{
		if (tmp->x > xmax)
			xmax = tmp->x;
		if (tmp->x < xmin)
			xmin = tmp->x;
		tmp = tmp->nx;
	}
	tmp = game->rmlst;
	while (tmp)
	{
		tmp->x -= xmin;
		tmp = tmp->nx;
	}
	return (((xmax - xmin) + 1));
}

int	ydim(t_game *game)
{
	t_room	*tmp;
	int xmax;
	int xmin;

	xmax = 0;
	xmin = 0;
	tmp = game->rmlst;
	while (tmp)
	{
		if (tmp->y > xmax)
			xmax = tmp->x;
		if (tmp->y < xmin)
			xmin = tmp->x;
		tmp = tmp->nx;
	}
	tmp = game->rmlst;
	while (tmp)
	{
		tmp->y -= xmin;
		tmp = tmp->nx;
	}
	return (((xmax - xmin) + 1));
}

void	popmap(char **map, int x, int y, t_game *game)
{
	int i;
	int j;
	t_room *tmp;

	tmp = game->rmlst;
	while (tmp)
	{
		map[tmp->x][tmp->y] = 'N';
		tmp = tmp->nx;
	}
	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			if (!(map[i][j] == 'N'))
				map[i][j] = '.';
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
}

char	**makemap(t_game *game)
{
	char	**map;
	int		y;
	int		x;
	int		i;

	y = ydim(game);
	x = xdim(game);
//	printf("x:%d  y:%d\n", x, y);
	map = malloc(sizeof(char *) * (x + 1));
	map[x] = NULL;
	i = 0;
	while (i < x)
	{
		map[i] = malloc(sizeof(char) * (y + 1));
		i++;
	}
//	printf("i:%d\n", i);
	popmap(map, x, y, game);
	return (map);
}
