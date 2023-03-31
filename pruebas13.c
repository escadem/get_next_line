#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BUFFER_SIZE 42

void	ft_leaks(void)
{
	system("leaks -q a.out");
}

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
	newstr = (char *)ft_calloc_str(len_s1 + len_s2 + 1);
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

//******************************************************************************
//******************************************************************************
//*************************   FUNCIONES ESPECIFICAS    *************************
//******************************************************************************
//******************************************************************************

char	*ft_initializing(int fd, char *rembuffer, int *nl_pos, int *byt_read)
{
	char	*str;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	*nl_pos = ft_check_nl(rembuffer);
	if (*nl_pos)
		return (NULL);
	str = (char *)ft_calloc_str(BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	*byt_read = read(fd, str, BUFFER_SIZE);
	if (*byt_read == -1 || *byt_read == 0)
	{
		free (str);
		return (NULL);
	}
	*nl_pos = ft_check_nl(str);
	return (str);
}

char	*ft_get_line(char *r_buffer, int *byt_read)
{
	char	*line;
	int		end_line;
	int		i;

	// printf("get_line: %s\n", r_buffer);
	if (*byt_read == -1)
	{
		free (r_buffer);
		return (NULL);
	}
	end_line = ft_check_nl(r_buffer);
	if (!end_line)
		return (r_buffer);
	line = (char *)ft_calloc_str(end_line + 1);
	if (!line)
	{
		free (r_buffer);
		return (NULL);
	}
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
	{
		// free (rbuffer);
		return (NULL);
	}
	tmp = (char *)ft_calloc_str(len_rbuffer - beg_buff + 1);
	if (!tmp || beg_buff == len_rbuffer)
	{
		free (rbuffer);
		free (tmp);
		return (NULL);
	}
	i = 0;
	while ((i + beg_buff) < len_rbuffer)
	{
		tmp[i] = rbuffer[i + beg_buff];
		i++;
	}
	free (rbuffer);
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
	//if (rem_buffer == NULL || !nl_pos)
		rem_buffer = ft_strjoin(rem_buffer, tmp_buffer);
	if (rem_buffer == NULL)
	{
		free (tmp_buffer);
		return (NULL);
	}
	while (!nl_pos && byt_read == BUFFER_SIZE)
	{
		byt_read = read(fd, tmp_buffer, BUFFER_SIZE);
		tmp_buffer[byt_read] = '\0';
		nl_pos = ft_check_nl(tmp_buffer);
		rem_buffer = ft_strjoin(rem_buffer, tmp_buffer);
	}
	line = ft_get_line(rem_buffer, &byt_read);
	rem_buffer = ft_clean_rem(rem_buffer, &nl_pos);
	free (tmp_buffer);
	return (line);
}

//******************************************************************************
//******************************************************************************
//*****************************   FUNCION MAIN    ******************************
//******************************************************************************
//******************************************************************************

int	main(void)
{
	int		fd;
	char	*linea;

	atexit(ft_leaks);

 	fd = open("a.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Opening file ERROR\n");
		return (1);
	}
	//
	linea = get_next_line(fd);
	while (linea != NULL)
	{
		// printf("%s\n\txxxx", linea);
		printf("%s", linea);
		free (linea);
		linea = get_next_line(fd);
	}
	if (!linea)
		printf("");
	//
	if (close(fd) == -1)
	{
		printf("Closing file ERROR");
		return (1);
	}
	return (0);
}
