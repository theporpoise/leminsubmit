/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 14:06:08 by mgould            #+#    #+#             */
/*   Updated: 2017/04/19 09:37:59 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <lem-in.h>

/*
** STRUCTS
*/

typedef struct	s_game
{
	int				nbr;
	struct s_room	*end;
	struct s_room	*start;
	struct s_room	*rmlst;
	struct s_lnk	*lnlst;
	char			**map;
	int				**edge;
	int				cap;
	struct s_path	*path;
	struct s_path	**routes;

}				t_game;

typedef struct	s_room
{
	char			*nm;
	int				id;
	int				x;
	int				y;
	struct s_room	*nx;
}				t_room;

typedef struct	s_lnk
{
	char			*a;
	char			*b;
	int				x;
	int				y;
	struct s_lnk	*nx;
}				t_lnk;

typedef struct	s_path
{
	int				*path;
	int				moves;
	struct s_path	*nx;
}				t_path;

/*
** PARSE FUNCTIONS
*/
int	ft_isnbr(char *ln);
int valantcount(char *ln, int *command, t_game *game);
int ft_getarraylen(char **array);
int duprmcoords(t_room *tmp, t_room *game);
int	isroom(char *ln, t_game *game);
int valstartorend(int sore, t_game *game);
int valroom(char *ln, int *command, t_game *game);
int roomexists(char *one, char *two, t_game *game);
int duplnk(char *one, char *two, t_game *game);
int islink(t_game *game, char *one, char *two);
int vallink(char *ln, t_game *game);
int valinput(char *ln, t_game *game);
int parseinput(t_game *game);

/*
** INIT STRUCT FUNCTIONS
*/
t_game	*makegame(void);
t_room	*makeroom(char *name, int x, int y);
t_lnk	*makelnk(char *one, char *two);
t_path	*makepath(int *array, int moves);
t_path	**routearray(int capacity);
/*
** DEBUG FUNCTIONS
*/
void	debug_game(t_game *game, char **map, int **edge);
void	debug_path(t_path *inpath);
void	debug_allpaths(t_game *game);
void	debug_routes(t_path **routes, t_game *game);


/*
** helper functions for return
*/


/*
** operation functions
*/

#endif
