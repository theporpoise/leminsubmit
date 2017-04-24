/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 19:43:23 by mgould            #+#    #+#             */
/*   Updated: 2016/12/05 19:44:39 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_make_word(char *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while ((s[i] != c) && (s[i] != '\0'))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while ((s[i] != c) && (s[i] != '\0'))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}
