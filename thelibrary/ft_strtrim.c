/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 17:33:04 by mgould            #+#    #+#             */
/*   Updated: 2016/12/06 08:01:24 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	int		i;
	int		len;
	int		k;
	char	*value;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	len = ft_strlen((char *)s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (s[i] == '\0')
	{
		value = (char *)malloc(sizeof(value) * 1);
		value[0] = '\0';
		return (value);
	}
	while ((s[len] == ' ') || (s[len] == '\n') || (s[len] == '\t'))
		len--;
	if (!(value = (char *)malloc((len - i + 2))))
		return (NULL);
	ft_fill_char(value, (char*)s, len, i);
	return (value);
}
