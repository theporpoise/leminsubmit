/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 18:30:33 by mgould            #+#    #+#             */
/*   Updated: 2017/04/19 09:44:32 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <lem-in.h>

/*
** DISPLAY MAP FUNCTIONS
*/

int	xdim(t_game *game)
{
	t_room	*tmp;
	int xmax;
	int xmin;

	xmax = 0;
	xmin = 0;
	tmp = game->rmlst;
	while (tmp)
	{
		if (tmp->x > xmax)
			xmax = tmp->x;
		if (tmp->x < xmin)
			xmin = tmp->x;
		tmp = tmp->nx;
	}
	tmp = game->rmlst;
	while (tmp)
	{
		tmp->x -= xmin;
		tmp = tmp->nx;
	}
	return (((xmax - xmin) + 1));
}


int	ydim(t_game *game)
{
	t_room	*tmp;
	int xmax;
	int xmin;

	xmax = 0;
	xmin = 0;
	tmp = game->rmlst;
	while (tmp)
	{
		if (tmp->y > xmax)
			xmax = tmp->x;
		if (tmp->y < xmin)
			xmin = tmp->x;
		tmp = tmp->nx;
	}
	tmp = game->rmlst;
	while (tmp)
	{
		tmp->y -= xmin;
		tmp = tmp->nx;
	}
	return (((xmax - xmin) + 1));
}

void	popmap(char **map, int x, int y, t_game *game)
{
	int i;
	int j;
	t_room *tmp;

	tmp = game->rmlst;
	while (tmp)
	{
		map[tmp->x][tmp->y] = 'N';
		tmp = tmp->nx;
	}
	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			if (!(map[i][j] == 'N'))
				map[i][j] = '.';
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
}

char	**makemap(t_game *game)
{
	char	**map;
	int		y;
	int		x;
	int		i;

	y = ydim(game);
	x = xdim(game);
//	printf("x:%d  y:%d\n", x, y);
	map = malloc(sizeof(char *) * (x + 1));
	map[x] = NULL;
	i = 0;
	while (i < x)
	{
		map[i] = malloc(sizeof(char) * (y + 1));
		i++;
	}
//	printf("i:%d\n", i);
	popmap(map, x, y, game);
	return (map);
}


/*
** EDGE MAP
*/


void	popedge(int **map, int len, t_game *game)
{
	int i;
	int j;
	t_lnk *tmp;

	tmp = game->lnlst;
	while (tmp)
	{
		map[tmp->x][tmp->y] = 1;
		map[tmp->y][tmp->x] = 1;
		tmp = tmp->nx;
	}
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			if (map[i][j] != 1)
				map[i][j] = 0;
			j++;
		}
		//setting terminal sentinal to negative one
		map[i][j] = -1;
		i++;
	}
}

void	lnkstoids(t_lnk *lnk, t_room *rm)
{
	t_room	*tmp;

	while (lnk)
	{
		tmp = rm;
		while(tmp)
		{
			if (!ft_strcmp(tmp->nm, lnk->a))
				lnk->x = tmp->id;
			if (!ft_strcmp(tmp->nm, lnk->b))
				lnk->y = tmp->id;
			tmp = tmp->nx;
		}
		lnk = lnk->nx;
	}
}

int	**makeedge(t_game *game)
{
	int	**edge;
	int	len;
	int i;

	//number of rooms is simply the highest id number, how nice :-)
	len = ((game->rmlst)->id + 1);
	//	printf("len:%d", len);
	edge = malloc(sizeof(int *) * (len + 1));
	edge[len] = NULL;
	i = 0;
	while (i < len)
	{
		edge[i] = malloc(sizeof(int) * (len + 1));
		//terminator sentinal set to -1
		i++;
	}
//	printf("i:%d\n", i;
	lnkstoids(game->lnlst, game->rmlst);
	popedge(edge, len, game);
	return (edge);
}



/*
** PATHFINDING NOTES
*/

void	networkcapacity(t_game *game)
{
	int i;
	int startcon;
	int endcon;

	i = 0;
	startcon = 0;
	endcon = 0;
	while((game->edge)[(game->start)->id][i] != -1)
	{
		if ((game->edge)[(game->start)->id][i] == 1)
			startcon++;
		i++;
	}
	i = 0;
	while((game->edge)[(game->end)->id][i] != -1)
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
	int moves;
	t_path *tmp;
	t_path *find;
	t_path *prev;

	//moves = path[(game->rmlst)->id] * -1;
	moves = (path[(game->rmlst)->id + 1] * -1) -1;
	tmp = makepath(path, moves);
	prev = NULL;
	find = game->path;
	if (!(game->path) && (game->path = tmp))
		return ;
	//if (find->moves >= moves) this weirdly workds on one case
	//if (find->moves <= moves)
	//if (find->moves < moves)
	if (find->moves >= moves)
	{
		tmp->nx = game->path;
		game->path = tmp;
		return ;
	}
	//while (find && (find->moves >= moves))
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
			//spawn[(end + 1)] -= 1;
			spawn[(game->rmlst)->id + 1] -= 1;
			//spawn[j] = spawn[end + 1] * -1;
			spawn[j] = spawn[(game->rmlst)->id + 1] * -1;
			allvalidpaths(game, end, spawn, j);
		}
		j++;
	}
	free(path);
}


/*
** FINDING ROUTES
*/

//NOTES
//if you can't find a route, return zero
//int		*idup(int *path)



t_path	*copypath(t_path *path)
{
	t_path *ret;

	ret = malloc(sizeof(t_path));
	ret->path = idup(path->path);
	ret->moves = path->moves;
	ret->nx = NULL;

	return (ret);
}

//check total moves vs. total nodes
//break if it doesn't work, and set to null
//break if route overlap


int		getrouten(t_path **routes, t_game *game, int n)
{
	int i;
	int ret;
	t_path *tmp;

	tmp = NULL;
	ret = 1;
	i = 0;

	while (i < (n + 1))
	{
	//	printf("getrouten one in  while\n");
		tmp = copypath(game->path);
		tmp->nx = routes[n];
		routes[n] = tmp;
		i++;
	}
//	printf("getrouten  two past while\n");
	//printf("paths in routes is %d\n", getroutelen(routes[n]));
	return (ret);
}

void	getroutes(t_game *game)
{
	int n;
	int i;

	i = 0;
	n = game->cap;
	game->routes = routearray(n);
	while (i < n)
	{
		getrouten(game->routes, game, i);
		i++;
	}

}

int	routefinder(t_game *game)
{
	int *path;

	path = malloc(sizeof(int) * (((game->rmlst)->id) + 2));
	ft_memset(path, 0, sizeof(path));
	path[((game->rmlst)->id) + 1] = -1;
	path[(game->start)->id] = (path[((game->rmlst)->id) + 1] * -1);

	allvalidpaths(game, (game->end)->id, path, (game->start)->id);
	printf("PRINTING ALL PATHS BEFORE ROUTE FUNCTIONS\n");
	debug_allpaths(game);
	if (!game->path)
		return (0);
	networkcapacity(game);
	//here is the error
	printf("AFTER CAPACITY IS %d\n", game->cap);
	//getroutes(game);

	//printf("AFTER GET ROUTES\n");
	//debug_routes(game->routes, game);

	return (1);
}


int main(void)
{
	t_game	*game;

	game = makegame();
	if (!parseinput(game))
	{
		//cleanup
		return (0);
	}

	//MAP FOR VISUALIZATION
	game->map = makemap(game);
	//MAP FOR SOLVING CONNECTIONS
	game->edge = makeedge(game);


	//FUNCTION THAT SOLVES IT

	if (!routefinder(game))
	{
		printf("there are no valid routes!\n");
	}

	//find shortest path
	//get routes
	//make ants
	//calcualte routs + paths and print ant-walk function

	//DEBUG
	debug_game(game, game->map, game->edge);

	//CLEANUP
	//create function that cleans up the game, everything is in the game
	//OR cleanup function can be a return value :-).
	free(game);
	return (0);
}




