/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edgemap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 09:59:36 by mgould            #+#    #+#             */
/*   Updated: 2017/04/20 20:29:51 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

void	popedge(int **map, int len, t_game *game)
{
	int		i;
	int		j;
	t_lnk	*tmp;

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
		while (tmp)
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

int		**makeedge(t_game *game)
{
	int	**edge;
	int	len;
	int i;

	len = ((game->rmlst)->id + 1);
	edge = malloc(sizeof(int *) * (len + 1));
	edge[len] = NULL;
	i = 0;
	while (i < len)
	{
		edge[i] = malloc(sizeof(int) * (len + 1));
		i++;
	}
	lnkstoids(game->lnlst, game->rmlst);
	popedge(edge, len, game);
	return (edge);
}
