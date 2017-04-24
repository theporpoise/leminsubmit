/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 22:05:09 by mgould            #+#    #+#             */
/*   Updated: 2017/04/08 22:56:59 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 60000
# include "libft.h"

typedef struct		s_list_1
{
	void			*rest;
	void			*start;
	int				rm;
	int				fd;
	struct s_list_1	*next;
}					t_list_1;

#endif
