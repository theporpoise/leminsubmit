/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edgemap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 09:59:36 by mgould            #+#    #+#             */
/*   Updated: 2017/04/19 10:01:39 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem-in.h>

void	popedge(int **map, int len, t_game *game)
{
	int i;
	int j;
	t_lnk *tmp;

	tmp = game->lnlst;
	while (tmp)
	{
		map[tmp->x][tmp->y] = 1;
		map[tmp->y][tmp->x] = 1;
		tmp = tmp->nx;
	}
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			if (map[i][j] != 1)
				map[i][j] = 0;
			j++;
		}
		//setting terminal sentinal to negative one
		map[i][j] = -1;
		i++;
	}
}

void	lnkstoids(t_lnk *lnk, t_room *rm)
{
	t_room	*tmp;

	while (lnk)
	{
		tmp = rm;
		while(tmp)
		{
			if (!ft_strcmp(tmp->nm, lnk->a))
				lnk->x = tmp->id;
			if (!ft_strcmp(tmp->nm, lnk->b))
				lnk->y = tmp->id;
			tmp = tmp->nx;
		}
		lnk = lnk->nx;
	}
}

int	**makeedge(t_game *game)
{
	int	**edge;
	int	len;
	int i;

	//number of rooms is simply the highest id number, how nice :-)
	len = ((game->rmlst)->id + 1);
	//	printf("len:%d", len);
	edge = malloc(sizeof(int *) * (len + 1));
	edge[len] = NULL;
	i = 0;
	while (i < len)
	{
		edge[i] = malloc(sizeof(int) * (len + 1));
		//terminator sentinal set to -1
		i++;
	}
//	printf("i:%d\n", i;
	lnkstoids(game->lnlst, game->rmlst);
	popedge(edge, len, game);
	return (edge);
}
