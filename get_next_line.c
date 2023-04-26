/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescat-l <eescat-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:37:36 by eescat-l          #+#    #+#             */
/*   Updated: 2023/04/26 20:02:59 by eescat-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_initializing(int fd, char *rembuffer, int *nl_pos, int *byt_read)
{
	char	*str;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	*nl_pos = ft_check_nl(rembuffer);
	if (*nl_pos)
		return (NULL);
	str = ft_calloc_str(BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	*byt_read = read(fd, str, BUFFER_SIZE);
	if (*byt_read == -1 || *byt_read == 0)
	{
		free (str);
		str = NULL;
		return (NULL);
	}
		// return (ft_free(&str));
	*nl_pos = ft_check_nl(str);
	return (str);
}

char	*ft_get_line(char *r_buffer, int *byt_read)
{
	char	*line;
	int		end_line;
	int		i;

	if (*byt_read == -1)
	{
		free (r_buffer);
		r_buffer = NULL;
		return (NULL);
	}
		// return (ft_free(&r_buffer));
	end_line = ft_check_nl(r_buffer);
	if (!end_line)
		return (r_buffer);
	line = ft_calloc_str(end_line + 1);
	if (!line)
	{
		free (r_buffer);
		r_buffer = NULL;
		return (NULL);
	}
		// return (ft_free(&r_buffer));
	i = -1;
	while (++i < end_line)
		line[i] = r_buffer[i];
	return (line);
}

char	*ft_clean_rem(char *rbuffer, int *nl_pos)
{
	char	*tmp;
	int		beg_buff;
	int		len_rbuffer;
	int		i;

	len_rbuffer = ft_strlen(rbuffer);
	beg_buff = ft_check_nl(rbuffer);
	if (!(*nl_pos))
		return (NULL);
	tmp = ft_calloc_str(len_rbuffer - beg_buff + 1);
	if (!tmp || beg_buff == len_rbuffer)
	{
		free (rbuffer);
		rbuffer = NULL;
		return (ft_free(&tmp));
	}
	i = 0;
	while ((i + beg_buff) < len_rbuffer)
	{
		tmp[i] = rbuffer[i + beg_buff];
		i++;
	}
	free (rbuffer);
	rbuffer = NULL;
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*rem_buffer;
	char		*tmp_buffer;
	char		*line;
	int			byt_read;
	int			nl_pos;

	tmp_buffer = ft_initializing(fd, rem_buffer, &nl_pos, &byt_read);
		rem_buffer = ft_strjoin(rem_buffer, tmp_buffer);
	if (rem_buffer == NULL)
	{
		if (tmp_buffer)
		{
			free (tmp_buffer);
			tmp_buffer = NULL;
		}
		return (NULL);
	}
	while (!nl_pos && byt_read == BUFFER_SIZE)
	{
		byt_read = read(fd, tmp_buffer, BUFFER_SIZE);
		if (byt_read == -1)
		// {
		// 	free (rem_buffer);
		// 	rem_buffer = NULL;   //DA ERROR DE LEAK SI SE QUITA
		// 	return (NULL);
		// }	
			return (ft_free(&rem_buffer));
		tmp_buffer[byt_read] = '\0';
		nl_pos = ft_check_nl(tmp_buffer);
		rem_buffer = ft_strjoin(rem_buffer, tmp_buffer);
	}
	line = ft_get_line(rem_buffer, &byt_read);
	rem_buffer = ft_clean_rem(rem_buffer, &nl_pos);
	free (tmp_buffer);
	tmp_buffer = NULL;
	return (line);
}
