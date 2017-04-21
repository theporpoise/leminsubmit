/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathhelpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 20:31:07 by mgould            #+#    #+#             */
/*   Updated: 2017/04/20 20:54:03 by mgould           ###   ########.fr       */
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
