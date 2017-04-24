/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 18:30:33 by mgould            #+#    #+#             */
/*   Updated: 2017/04/23 22:36:01 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

static void	pathsandroutes(t_game *game)
{
	int		i;
	t_path	*ptmp;

	i = 0;
	while (game->path)
	{
		ptmp = (game->path)->nx;
		free((game->path)->path);
		free((game->path));
		game->path = ptmp;
	}
	while ((game->routes)[i])
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
}

static void	mapandedges(t_game *game, int len)
{
	int i;

	i = 0;
	while ((game->map)[i])
	{
		free((game->map)[i]);
		i++;
	}
	free(game->map);
	i = 0;
	while (i <= len)
	{
		free((game->edge)[i]);
		i++;
	}
	free(game->edge);
}

static void	rmsandlsts(t_game *game)
{
	t_lnk	*ltmp;
	t_room	*rtmp;

	while (game->lnlst)
	{
		ltmp = (game->lnlst)->nx;
		free((game->lnlst)->a);
		free((game->lnlst)->b);
		free(game->lnlst);
		game->lnlst = ltmp;
	}
	while (game->rmlst)
	{
		rtmp = (game->rmlst)->nx;
		free((game->rmlst)->nm);
		free((game->rmlst));
		game->rmlst = rtmp;
	}
}

static int	freethemalloc(t_game **gamepointer)
{
	int		len;
	t_game	*game;
	t_ant	*ant;

	game = *gamepointer;
	len = (game->rmlst)->id;
	ant = game->ant;
	rmsandlsts(game);
	mapandedges(game, len);
	pathsandroutes(game);
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

int			main(void)
{
	t_game	*game;

	game = makegame();
	if (!parseinput(game))
	{
		return (freethemalloc(&game));
	}
	game->map = makemap(game);
	game->edge = makeedge(game);
	if (!routefinder(game))
	{
		printf("Error\nThere are no valid routes!\n");
		return (freethemalloc(&game));
	}
	routecount(game);
	routecap(game);
	antmarch(game);
	return (freethemalloc(&game));
}
