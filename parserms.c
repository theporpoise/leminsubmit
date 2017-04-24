/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 09:29:32 by mgould            #+#    #+#             */
/*   Updated: 2017/04/24 01:17:24 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

int	duprmcoords(t_room *tmp, t_room *game)
{
	t_room *xy;

	xy = game;
	while (xy)
	{
		if (xy->x == tmp->x && xy->y == tmp->y)
			return (1);
		xy = xy->nx;
	}
	xy = game;
	while (xy)
	{
		if (!ft_strcmp(xy->nm, tmp->nm))
			return (1);
		xy = xy->nx;
	}
	return (0);
}

int	isroom(char *ln, t_game *game)
{
	char	**words;
	t_room	*tmp;

	if (*ln == '#')
		return (2);
	tmp = NULL;
	words = ft_strsplit(ln, ' ');
	if (*ln == 'L' || (ft_getarraylen(words) != 3) || ft_strchr(words[0], '-') \
			|| !ft_isnbr(words[1]) || !ft_isnbr(words[2]))
		return (fwords(words, 0, tmp));
	tmp = makeroom(words[0], ft_atoi(words[1]), ft_atoi(words[2]));
	if (duprmcoords(tmp, game->rmlst))
		return (fwords(words, 0, tmp));
	tmp->nx = game->rmlst;
	game->rmlst = tmp;
	free(words[1]);
	free(words[2]);
	free(words);
	return (1);
}

int	valstartorend(int sore, t_game *game)
{
	char	*check;
	int		i;

	get_next_line(0, &check);
	if (!(ft_strcmp("##end", check) || !ft_strcmp("##start", check)))
		;
	else if ((i = isroom(check, game)) == 0)
		;
	else if (i == 2)
	{
		free(check);
		i = valstartorend(sore, game);
		return (i);
	}
	else if (i == 1 && sore == 1)
		game->start = game->rmlst;
	else if (i == 1 && sore == 0)
		game->end = game->rmlst;
	ft_putstr(check);
	ft_putstr("\n");
	free(check);
	return (2);
}

int	valroom(char *ln, int *command, t_game *game)
{
	static int start;
	static int end;

	if ((!ft_strcmp("##end", ln) && (end > 0)) ||
		(((!ft_strcmp("##start", ln)) && (start > 0))))
		return (0);
	else if (!(ft_strcmp("##start", ln)) && start == 0)
	{
		ft_printf("##start\n");
		start++;
		return (valstartorend(1, game));
	}
	else if (!(ft_strcmp("##end", ln)) && end == 0)
	{
		ft_printf("##end\n");
		end++;
		return (valstartorend(0, game));
	}
	else if (*ln == '#')
		return (2);
	else if (isroom(ln, game))
		return (1);
	*command = 2;
	return (3);
}

int	roomexists(char *one, char *two, t_game *game)
{
	t_room	*rm;
	int		flag;

	rm = game->rmlst;
	flag = 0;
	while (rm)
	{
		if (!ft_strcmp(one, rm->nm))
		{
			flag = 1;
			break ;
		}
		rm = rm->nx;
	}
	rm = game->rmlst;
	while (rm)
	{
		if (!ft_strcmp(two, rm->nm))
		{
			flag += 1;
			break ;
		}
		rm = rm->nx;
	}
	return (flag == 2 ? 1 : 0);
}
