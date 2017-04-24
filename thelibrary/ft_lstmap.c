/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:02:41 by mgould            #+#    #+#             */
/*   Updated: 2016/12/05 14:57:43 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <stdio.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*nl;
	t_list	*head;

	if (!lst)
		return (NULL);
	nl = NULL;
	nl = (t_list *)malloc(sizeof(t_list));
	if (!(nl))
		return (NULL);
	nl = f(lst);
	head = nl;
	lst = lst->next;
	while (lst)
	{
		nl->next = f(lst);
		nl = nl->next;
		lst = lst->next;
	}
	return (head);
}
