/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathhelpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 20:31:07 by mgould            #+#    #+#             */
/*   Updated: 2017/04/24 01:11:04 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

t_path	*copypath(t_path *path)
{
	t_path *ret;

	ret = malloc(sizeof(t_path));
	ret->path = idup(path->path);
	ret->moves = path->moves;
	ret->origin = path;
	ret->nx = NULL;
	return (ret);
}

void	releasepath(t_path *path)
{
	if (!path)
		return ;
	if (path->path)
		free(path->path);
	free(path);
}

int		enoughpaths(t_path **routes, int n)
{
	int		i;
	t_path	*tmp;

	tmp = routes[n];
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->nx;
	}
	if (i != (n + 1))
	{
		return (0);
	}
	return (1);
}

int		fwords(char **words, int ret, t_room *tmp)
{
	int i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
	if (tmp)
		free(tmp);
	return (ret);
}

void	antsandcap(t_game *game)
{
	t_ant	*ant;

	ant = game->ant;
	free(game->rcap);
	while (game->ant)
	{
		ant = (game->ant)->nx;
		free(game->ant);
		game->ant = ant;
	}
}
