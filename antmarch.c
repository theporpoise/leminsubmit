/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antmarch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 09:01:17 by mgould            #+#    #+#             */
/*   Updated: 2017/04/23 23:01:34 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

static char	*matchnumber(t_game *game, t_ant *ant)
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

static int	alldone(t_ant *ant)
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

static void	printants(t_game *game, t_ant *tmp)
{
	char	*name;
	int		flag;

	flag = 0;
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
				ft_printf(" ");
			ft_putstr("L");
			ft_putnbr(tmp->nbr);
			ft_putstr("-");
			ft_putstr(name);
			flag = 1;
		}
		tmp->step += 1;
		tmp = tmp->nx;
	}
}

void		antmarch(t_game *game)
{
	t_path	*route;
	t_ant	*nextant;

	while (game->nbr)
	{
		route = selectroute(game);
		while (route)
		{
			nextant = makeant(route);
			route = route->nx;
			nextant->nx = game->ant;
			game->ant = nextant;
			game->nbr -= 1;
		}
		printants(game, game->ant);
		ft_printf("\n");
	}
	while (!alldone(game->ant))
	{
		printants(game, game->ant);
		if (!alldone(game->ant))
			ft_printf("\n");
	}
}
