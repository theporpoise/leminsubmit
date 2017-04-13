/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 14:06:08 by mgould            #+#    #+#             */
/*   Updated: 2017/04/13 13:08:14 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
#include "libft.h"
#include <stdlib.h>

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
	struct s_lnk	*nx;
}				t_lnk;

/*
** INIT STRUCT FUNCTIONS
*/
t_game	*makegame(void);
t_room	*makeroom(char *name, int x, int y);
t_lnk	*makelnk(char *one, char *two);
/*
** DEBUG FUNCTIONS
*/



/*
** helper functions for return
*/


/*
** operation functions
*/

#endif
