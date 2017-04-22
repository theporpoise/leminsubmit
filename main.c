/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 18:30:33 by mgould            #+#    #+#             */
/*   Updated: 2017/04/21 21:28:10 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

void	routecount(t_game *game)
{
	int 	i;
	t_path	**tmp;

	i = 0;
	tmp = game->routes;
	while (tmp[i])
	{
		i++;
	}
	game->rnbr = i;
}

int		singleroutecap(t_path *path)
{
	int i;
	int j;

	j = 0;
	while (path)
	{
		i = 0;
		while ((path->path)[i] > -1)
		{
			if ((path->path)[i] != 1 && (path->path)[i] > 0)
				j++;
			i++;
		}
		path = path->nx;
	}
	return (j);
}

void	routecap(t_game *game)
{
	int		i;
	int		*ret;

	i = 0;
	ret = malloc(sizeof(int) * (game->rnbr + 1));
	while (i < game->rnbr)
	{
		ret[i] = singleroutecap((game->routes)[i]);
		i++;
	}
	ret[i] = -1;
	game->rcap = ret;
}

t_path	*selectroute(t_game *game)
{
	int i;

	i = 0;
	while ((game->nbr > game->rcap[i]))
	{
		if (game->rcap[i + 1] == -1)
			break ;
		i++;
	}
	return ((game->routes)[i]);
}

char	*matchnumber(t_game *game, t_ant *ant)
{
	int		i;
	t_room	*rooms;
	char	*ret;

	i = 0;
	rooms = game->rmlst;
	while (ant->step != ant->path[i])
	{
		if (ant->path[i] < 0)
		{
			ant->donezo = 1;
			return (NULL);
		}
		i++;
	}
	while (rooms->id != i)
	{
		rooms = rooms->nx;
	}
	ret = rooms->nm;
	return (ret);
}

int		alldone(t_ant *ant)
{
	int		i;
	t_ant	*tmp;

	i = 0;
	tmp = ant;
	while (tmp)
	{
		if (!(tmp->donezo))
		{
			return (0);
		}
		tmp = tmp->nx;
	}
	return (1);
}

void	printants(t_game *game, t_ant *ant)
{
	t_ant	*tmp;
	char	*name;
	int		flag;

	flag = 0;
	tmp = ant;
	while (tmp)
	{
		if (tmp->donezo)
		{
			tmp = tmp->nx;
			continue;
		}
		if ((name = matchnumber(game, tmp)))
		{
			if (flag == 1)
				printf(" ");
			printf("L%d-%s", tmp->nbr, name);
			flag = 1;
		}
		tmp->step += 1;
		tmp = tmp->nx;

	}
}

void	antmarch(t_game *game)
{
	t_path	*route;
	t_ant	*nextant;

	while (game->nbr)
	{
		route = selectroute(game);
		while(route)
		{
			nextant = makeant(route);
			route = route->nx;

			nextant->nx = game->ant;
			game->ant = nextant;
			game->nbr -= 1;
		}
		printants(game, game->ant);
		printf("\n");
	}
	while (!alldone(game->ant))
	{
		printants(game, game->ant);
		if (!alldone(game->ant))
			printf("\n");
	}
}

int main(void)
{
	t_game	*game;

	game = makegame();
	if (!parseinput(game))
	{
		return (0);
	}
	game->map = makemap(game);
	game->edge = makeedge(game);
	if (!routefinder(game))
	{
		printf("Error\nThere are no valid routes!\n");
		//free everything
		return (0);
	}
	routecount(game);
	routecap(game);
	antmarch(game);
	//free everything
	free(game);
	return (0);
}







