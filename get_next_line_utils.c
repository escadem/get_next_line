/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescat-l <eescat-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:37:26 by eescat-l          #+#    #+#             */
/*   Updated: 2023/04/01 10:13:06 by eescat-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
			i++;
	}
	return (i);
}

char	*ft_calloc_str(size_t count)
{
	char	*p;
	size_t	i;

	if (count > SIZE_MAX)
		return (NULL);
	p = malloc(count);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}

int	ft_check_nl(char *string)
{
	int	position;

	position = 0;
	if (string == 0)
		return (0);
	while (*(string + position) != '\0')
	{
		if (*(string + position) != '\n')
			position++;
		else
			return (position + 1);
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	int		len_s1;
	int		len_s2;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	newstr = ft_calloc_str(len_s1 + len_s2 + 1);
	if (newstr == NULL)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		newstr[i] = s1[i];
	i = len_s1 - 1;
	while (++i < len_s1 + len_s2)
		newstr[i] = s2[i - len_s1];
	free (s1);
	return (newstr);
}
