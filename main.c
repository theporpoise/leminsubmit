/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 18:30:33 by mgould            #+#    #+#             */
/*   Updated: 2017/04/19 08:57:21 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <lem-in.h>


/*
** DEBUG FUNCTIONS
*/

void	debug_game(t_game *game, char **map, int **edge)
{
	int i;
	int j;

	if (!game || !(game->rmlst) || !(game->lnlst))
		return ;
	printf("YOU ARE IN DEBUG MODE\n");
	//debug ant number
	if (game->nbr)
		printf("ANT NUMBER:%d\n", game->nbr);
	//debug start and end
	printf("\nBEGIN AND END NODES\n");
	printf("START\n%-24s%d\t%d\t%d\n", (game->start)->nm, (game->start)->id, \
		   	(game->start)->x, (game->start)->y);
	printf("END\n%-24s%d\t%d\t%d\n\n", (game->end)->nm, (game->end)->id, \
		   	(game->end)->x, (game->end)->y);
	//debug rooms
	/*
	printf("\nROOMS:\n");
	printf("Name\t\t\tID\tX\tY\t\n");

	while (game->rmlst)
	{
		printf("%-24s%d\t%d\t%d\n", (game->rmlst)->nm, (game->rmlst)->id, \
			   	(game->rmlst)->x, (game->rmlst)->y);
		game->rmlst = (game->rmlst)->nx;
	}
	*/
	//debug links

	printf("\nLINKS:\n");
	while (game->lnlst)
	{
		printf("%s\t%s\n", (game->lnlst)->a, (game->lnlst)->b);
		game->lnlst = (game->lnlst)->nx;
	}

	printf("\nMAP:\n");
	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}

	printf("\nEDGE:\n");
	i = 0;
	while (edge[i])
	{
		j = 0;
		while (edge[i][j] != -1)
		{
			printf("%-2d ", edge[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	//Debug SOLVER
	printf("capacity:%d\n", game->cap);
}


/*
** PARSING NOTES
*/

/*
 * Rooms can be separated by multiple spaces
 * Room name can NOT start with an L
 * Room names can NOT contain a '-' b/c undefined behavior for links
 * I ignore leading or trailing white space for rooms
 * Must provide 2 coordinates which are numbers.
 * I allow negative (-) and (+) numbers for coordinates.
 * I do NOT allow duplicate coordinates for 2 diff rooms b/c laws of physics!
 * I do NOT allow duplicate room names, even with diff coords,
 * 		b/c i wouldn't know where to send the ants
 * I IGNORE duplicate links or links to self
 * I only allow ONE start or end due to undefined behavior otherwise.
*/

/*
** PARSING FUNCTIONS
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
	if (!ft_strcmp("##end", ln) ||!ft_strcmp("##start", ln))
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

int ft_getarraylen(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return i;
}


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

int isroom(char *ln, t_game *game)
{
	char	**words;
	t_room	*tmp;

	if (*ln == '#')
		return (2);
	tmp = NULL;
	words = ft_strsplit(ln, ' ');
	if (*ln == 'L' || (ft_getarraylen(words) != 3) || ft_strchr(words[0], '-') \
			|| !ft_isnbr(words[1]) || !ft_isnbr(words[2]))
		return (0);
	tmp = makeroom(words[0], atoi(words[1]), atoi(words[2]));
	free(words[1]);
	free(words[2]);
	free(words);
	if (duprmcoords(tmp, game->rmlst))
		return (0);
	tmp->nx = game->rmlst;
	game->rmlst = tmp;
	return (1);
}



int valstartorend(int sore, t_game *game)
{
	char *check;
	int i;

	get_next_line(0, &check);
	if (!(ft_strcmp("##end", check) || !ft_strcmp("##start", check)))
		return (0);
	if ((i = isroom(check, game)) == 0)
		return (0);
	if (i == 2)
	{
		i = valstartorend(sore, game);
		free(check);
		return (i);
	}
	else if (i == 1 && sore == 1)
		game->start = game->rmlst;
	else if (i == 1 && sore == 0)
		game->end = game->rmlst;
	printf("%s\n", check);
	free(check);
	return (2);
}



int valroom(char *ln, int *command, t_game *game)
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

int roomexists(char *one, char *two, t_game *game)
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
			break;
		}
		rm = rm->nx;
	}
	rm = game->rmlst;
	while (rm)
	{
		if (!ft_strcmp(two, rm->nm))
		{
			flag += 1;
			break;
		}
		rm = rm->nx;
	}
	return (flag == 2 ? 1 : 0);
}

int duplnk(char *one, char *two, t_game *game)
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
			break;
		}
		lnk = lnk->nx;
	}
	return (flag);
}

int islink(t_game *game, char *one, char *two)
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


int vallink(char *ln, t_game *game)
{
	char	**words;
	int 	ret;

	ret = 0;
	words = ft_strsplit(ln, '-');
	if (!(game->end) || !(game->start) || !(game->rmlst))
	{
		ret = 0;
	}
	else if (!ft_strcmp("##end", ln) ||!ft_strcmp("##start", ln))
	{
		ret = 0;
	}
	else if (*ln == '#')
	{
		ret = 2;
	}
	else if (ft_getarraylen(words) != 2 || words[0][0] == 'L' || words[1][0] == 'L')
	{
		ret = 0;
	}
	else if (!(roomexists(words[0], words[1], game)))
	{
		ret = 0;
	}
	else if (!ft_strcmp(words[0], words[1]))
	{
		ret = 1;
	}
	else
		ret = islink(game, words[0], words[1]);
	free(words);
	return (ret);
}

int	valinput(char *ln, t_game *game)
{
	static int command;
	int i;

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

int	parseinput(t_game *game)
{
	char *line;
	int i;


	i = 0;
	while (get_next_line(0, &line) > 0)
	{
		if (!(i = valinput(line, game)))
		{
			printf("Error\n");
			free(line);
			//OR return the cleanup function :-).
			return (0) ;
		}
		else if (i == 1)
			//printf("%s\n", line);
		free(line);
	}
	printf("\n");
	return (1);
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


void	debug_path(t_path *inpath)
{
	int i;
	int *path;

	path = inpath->path;
	printf("moves is:%d ", inpath->moves);
	printf("path array: ");
	i = 0;
	while (path[i] > -1)
	{
		printf("%d, ", path[i]);
		i++;
	}
	printf("%d, ", path[i]);
	printf("\n");


}

void	debug_allpaths(t_game *game)
{
	t_path *tmp;
	int i;

	printf("printing all paths\n");
	i = 0;
	tmp = game->path;
	while (tmp)
	{
		debug_path(tmp);
		tmp = tmp->nx;
		i++;
	}
	printf("number of paths is %d\n\n", i);
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

void	debug_routes(t_path **routes, t_game *game)
{
	t_path **tmp;
	t_path	*tpath;
	int i;

	i = 0;
	if (!routes)
		return ;
	tmp = routes;
	printf("in debug routes\n");
	while ((i < game->cap))
	{
		tpath = tmp[i];
		printf("iterating through paths in route:%d\n", i);
		while (tpath)
		{
			debug_path(tpath);
			tpath = tpath->nx;
		}
		i++;
	}
	printf("total # of routes is %d\n", i);
}

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




