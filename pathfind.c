/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 10:04:08 by mgould            #+#    #+#             */
/*   Updated: 2017/04/20 20:52:54 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

void	networkcapacity(t_game *game)
{
	int i;
	int startcon;
	int endcon;

	i = 0;
	startcon = 0;
	endcon = 0;
	while ((game->edge)[(game->start)->id][i] != -1)
	{
		if ((game->edge)[(game->start)->id][i] == 1)
			startcon++;
		i++;
	}
	i = 0;
	while ((game->edge)[(game->end)->id][i] != -1)
	{
		if ((game->edge)[(game->end)->id][i] == 1)
			endcon++;
		i++;
	}
	game->cap = (startcon < endcon ? startcon : endcon);
}

int		*idup(int *path)
{
	int i;
	int *spawn;

	i = 0;
	while (path[i] >= 0)
		i++;
	spawn = malloc(sizeof(int) * (i + 1));
	i = 0;
	while (path[i] >= 0)
	{
		spawn[i] = path[i];
		i++;
	}
	spawn[(i)] = path[(i)];
	return (spawn);
}

void	addtopathlist(t_game *game, int *path)
{
	int		moves;
	t_path	*tmp;
	t_path	*find;
	t_path	*prev;

	moves = (path[(game->rmlst)->id + 1] * -1) - 1;
	tmp = makepath(path, moves);
	prev = NULL;
	find = game->path;
	if (!(game->path) && (game->path = tmp))
		return ;
	if (find->moves >= moves)
	{
		tmp->nx = game->path;
		game->path = tmp;
		return ;
	}
	while (find && (find->moves < moves))
	{
		prev = find;
		find = find->nx;
	}
	prev->nx = tmp;
	tmp->nx = find;
}

void	allvalidpaths(t_game *game, int end, int *path, int start)
{
	int node;
	int j;
	int *spawn;

	node = start;
	j = 0;
	if (path[end] > 0)
	{
		addtopathlist(game, path);
		return ;
	}
	while ((game->edge)[node][j] >= 0)
	{
		if (path[j] == 0 && game->edge[node][j] == 1)
		{
			spawn = idup(path);
			spawn[(game->rmlst)->id + 1] -= 1;
			spawn[j] = spawn[(game->rmlst)->id + 1] * -1;
			allvalidpaths(game, end, spawn, j);
		}
		j++;
	}
	free(path);
}
