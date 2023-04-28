/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescat-l <eescat-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:37:36 by eescat-l          #+#    #+#             */
/*   Updated: 2023/04/28 16:39:27 by eescat-l         ###   ########.fr       */
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
		return (ft_free_str(str));
	*nl_pos = ft_check_nl(str);
	return (str);
}

char	*ft_get_line(char *r_buffer, int *byt_read)
{
	char	*line;
	int		end_line;
	int		i;

	if (*byt_read == -1)
		return (ft_free_str(r_buffer));
	end_line = ft_check_nl(r_buffer);
	if (!end_line)
		return (r_buffer);
	line = ft_calloc_str(end_line + 1);
	if (!line)
		return (ft_free_str(r_buffer));
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
		return (ft_free_str(tmp));
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
		return (ft_free_str(tmp_buffer));
	while (!nl_pos && byt_read == BUFFER_SIZE)
	{
		byt_read = read(fd, tmp_buffer, BUFFER_SIZE);
		if (byt_read == -1)
			return (ft_free_str(rem_buffer));
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
