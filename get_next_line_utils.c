/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescat-l <eescat-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:37:26 by eescat-l          #+#    #+#             */
/*   Updated: 2023/03/31 23:13:50 by eescat-l         ###   ########.fr       */
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

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	i;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	p = (void *)malloc(count * size);
	if (p == NULL)
		return (NULL);
	i = -1;
	while (++i < count * size)
		*(unsigned char *)(p + i) = (unsigned char) 0;
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
	if (!s1)
	{
		s1 = (char *)ft_calloc(1, sizeof(char));
		if (!s1)
			return (NULL);
	}
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	newstr = (char *)ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	if (newstr == NULL)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		newstr[i] = s1[i];
	i = len_s1 - 1;
	while (++i < len_s1 + len_s2)
		newstr[i] = s2[i - len_s1];
	return (newstr);
}

