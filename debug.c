/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 09:08:50 by mgould            #+#    #+#             */
/*   Updated: 2017/04/20 16:20:47 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <lem-in.h>


/*
** DEBUG FUNCTIONS
*/

void	debug_edge(int **edge)
{
	int i;
	int j;

	printf("\nEDGE:\n");
	i = 0;
	while (edge[i])
	{
		j = 0;
		while (edge[i][j] != -1)
		{
			printf("%-2d ", edge[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	debug_game(t_game *game, char **map, int **edge)
{
	int i;
	//int j;

	if (!game || !(game->rmlst) || !(game->lnlst))
		return ;
	printf("YOU ARE IN DEBUG MODE\n");
	//debug ant number
	if (game->nbr)
		printf("ANT NUMBER:%d\n", game->nbr);
	//debug start and end
	printf("\nBEGIN AND END NODES\n");
	printf("START\n%-24s%d\t%d\t%d\n", (game->start)->nm, (game->start)->id, \
		   	(game->start)->x, (game->start)->y);
	printf("END\n%-24s%d\t%d\t%d\n\n", (game->end)->nm, (game->end)->id, \
		   	(game->end)->x, (game->end)->y);
	//debug rooms
	/*
	printf("\nROOMS:\n");
	printf("Name\t\t\tID\tX\tY\t\n");

	while (game->rmlst)
	{
		printf("%-24s%d\t%d\t%d\n", (game->rmlst)->nm, (game->rmlst)->id, \
			   	(game->rmlst)->x, (game->rmlst)->y);
		game->rmlst = (game->rmlst)->nx;
	}
	*/
	//debug links

	printf("\nLINKS:\n");
	while (game->lnlst)
	{
		printf("%s\t%s\n", (game->lnlst)->a, (game->lnlst)->b);
		game->lnlst = (game->lnlst)->nx;
	}

	printf("\nMAP:\n");
	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}

	debug_edge(edge);

	//Debug SOLVER
	printf("capacity:%d\n", game->cap);
}


void	debug_path(t_path *inpath)
{
	int i;
	int *path;

	path = inpath->path;
	printf("moves is:%d path array: ", inpath->moves);
	i = 0;
	while (path[i] > -1)
	{
		printf("%d, ", path[i]);
		i++;
	}
	printf("%d, ", path[i]);
	printf("\n");


}

void	debug_allpaths(t_game *game)
{
	t_path *tmp;
	int i;

	printf("PRINTING ALL PATHS\n");
	i = 0;
	tmp = game->path;
	while (tmp)
	{
		debug_path(tmp);
		tmp = tmp->nx;
		i++;
	}
	printf("number of paths is %d\n\n", i);
}

void	debug_routes(t_path **routes, t_game *game)
{
	t_path **tmp;
	t_path	*tpath;
	int i;

	i = 0;
	if (!routes)
		return ;
	tmp = routes;
	while ((i < (game->cap)) && tmp[i])
	{
		tpath = tmp[i];
		printf("iterating through paths in route:%d\n", i);
		while (tpath)
		{
			debug_path(tpath);
			tpath = tpath->nx;
		}
		i++;
	}
	printf("total # of routes is %d\n", i);
}
