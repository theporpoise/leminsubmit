/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parselnks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 09:32:44 by mgould            #+#    #+#             */
/*   Updated: 2017/04/24 00:17:20 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

int	duplnk(char *one, char *two, t_game *game)
{
	t_lnk	*lnk;
	int		flag;

	lnk = game->lnlst;
	flag = 0;
	while (lnk)
	{
		if (!ft_strcmp(one, lnk->a) && !ft_strcmp(two, lnk->b))
		{
			flag = 1;
			break ;
		}
		lnk = lnk->nx;
	}
	return (flag);
}

int	islink(t_game *game, char *one, char *two)
{
	t_lnk	*tmp;

	tmp = NULL;
	if (duplnk(one, two, game))
	{
		return (1);
	}
	tmp = makelnk(one, two);
	tmp->nx = game->lnlst;
	game->lnlst = tmp;
	return (1);
}

int	vallink(char *ln, t_game *game)
{
	char	**words;
	int		ret;

	ret = 0;
	words = ft_strsplit(ln, '-');
	if (!(game->end) || !(game->start) || !(game->rmlst))
		ret = 0;
	else if (!ft_strcmp("##end", ln) || !ft_strcmp("##start", ln))
		ret = 0;
	else if (*ln == '#')
		ret = 2;
	else if (ft_getarraylen(words) != 2 || words[0][0] == 'L' \
			|| words[1][0] == 'L')
		ret = 0;
	else if (!(roomexists(words[0], words[1], game)))
		ret = 0;
	else if (!ft_strcmp(words[0], words[1]))
		ret = 1;
	else
		ret = islink(game, words[0], words[1]);
	if (ret == 0)
		fwords(words, 0, NULL);
	else
		free(words);
	return (ret);
}
