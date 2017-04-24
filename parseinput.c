/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseinput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 09:14:31 by mgould            #+#    #+#             */
/*   Updated: 2017/04/23 23:04:53 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

/*
** PARSING NOTES
*/

/*
** Rooms can be separated by multiple spaces
** Room name can NOT start with an L
** Room names can NOT contain a '-' b/c undefined behavior for links
** I ignore leading or trailing white space for rooms
** Must provide 2 coordinates which are numbers.
** I allow negative (-) and (+) numbers for coordinates.
** I do NOT allow duplicate coordinates for 2 diff rooms b/c laws of physics!
** I do NOT allow duplicate room names, even with diff coords,
** 		b/c i wouldn't know where to send the ants
** I IGNORE duplicate links or links to self
** I only allow ONE start or end due to undefined behavior otherwise.
*/

int	ft_isnbr(char *ln)
{
	if (*ln == '+' || *ln == '-')
		ln++;
	while (*ln)
	{
		if (ft_isdigit(*ln))
			ln++;
		else
			return (0);
	}
	return (1);
}

int	valantcount(char *ln, int *command, t_game *game)
{
	if (!ft_strcmp("##end", ln) || !ft_strcmp("##start", ln))
		return (0);
	if (*ln == '#')
		return (2);
	else if (ft_isnbr(ln))
	{
		*command = 1;
		if (ft_atoi(ln) < 1)
			return (0);
		game->nbr = ft_atoi(ln);
		return (1);
	}
	return (0);
}

int	ft_getarraylen(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	valinput(char *ln, t_game *game)
{
	static int	command;
	int			i;

	i = 0;
	if (command == 0)
	{
		return (valantcount(ln, &command, game));
	}
	else if (command == 1 && (i = valroom(ln, &command, game)) != 3)
	{
		return (i);
	}
	else if (command == 2)
	{
		return (vallink(ln, game));
	}
	return (0);
}

int	parseinput(t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	while (get_next_line(0, &line) > 0)
	{
		if (!(i = valinput(line, game)))
		{
			ft_printf("Error\n");
			free(line);
			return (0);
		}
		else if (i == 1)
		{
			ft_putstr(line);
			ft_putstr("\n");
		}
		free(line);
	}
	ft_printf("\n");
	return (1);
}
