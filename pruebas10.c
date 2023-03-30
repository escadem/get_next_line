#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BUFFER_SIZE 3

/// @brief standard string lenthe function
/// @param s String which length must be calculated
/// @return the length of the string
int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i ++;
	return (i);
}

/// @brief finds out where the '\\n' is.
/// 	   If not available, returns 0
/// @param string 
/// @return 
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

/// @brief Libft project function. Joins to different strings in one
/// @param s1 String 1
/// @param s2 String 2
/// @return the pointer to the new string
char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	int		len_s1;
	int		len_s2;
	int		i;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	newstr = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		newstr[i] = s1[i];
	i = len_s1 - 1;
	while (++i < len_s1 + len_s2)
		newstr[i] = s2[i - len_s1];
	newstr[len_s1 + len_s2] = '\0';
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
	str = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
	{
		free (rembuffer);
		return (NULL);
	}
	*byt_read = read(fd, str, BUFFER_SIZE);
	if (*byt_read == -1)
	{
		free (rembuffer);
		return (NULL);
	}
	str[*byt_read] = '\0';
	return (str);
}

// char	*ft_clean_temp(char *t_buffer, int nl_pos, int byt_read)
// {
// 	char	*aux;
// 	int		i;

// 	i = byt_read - 1;
// 	if (!nl_pos && byt_read < BUFFER_SIZE)
// 	{
// 		while (++i < BUFFER_SIZE)
// 			t_buffer[i] = '\0';
// 	}
// 	aux = (char *)malloc((nl_pos + 1) * sizeof(char));
// 	if (!aux)
// 	{
// 		free (t_buffer);
// 		return (NULL);
// 	}
// 	i = -1;
// 	while (++i < nl_pos)
// 		aux[i] = t_buffer[i];
// 	aux[nl_pos] = '\0';
// 	return (aux);
// }

char	*ft_get_line(char *r_buffer, int *byt_read)
{
	char	*line;
	int		end_line;
	int		i;

	if (*byt_read == -1)
	{
		free (r_buffer);
		return (NULL);
	}
	end_line = ft_check_nl(r_buffer);
	if (!end_line)
		return (r_buffer);
	line = (char *)malloc((end_line + 1) * sizeof(char));
	if (!line)
	{
		free (r_buffer);
		return (NULL);
	}
	i = -1;
	while (++i < end_line)
		line[i] = r_buffer[i];
	line[end_line] = '\0';
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
// QUE PASA SI ES EL FINAL DEL ARCHIVO
		return (NULL);
	i = 0;
	tmp = (char *)malloc((len_rbuffer - beg_buff + 1) * sizeof(char));
	if (!tmp)
	{
		free(rbuffer);
		return (NULL);
	}
	while ((i + beg_buff) < len_rbuffer)
	{
		tmp[i] = rbuffer[i + beg_buff];
		i++;
	}
	tmp[i] = '\0';
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
	if (rem_buffer == NULL || nl_pos == 0)
		rem_buffer = ft_strjoin(rem_buffer, tmp_buffer);
// OJO PUEDE HABER PROBLEMAS EN EL STRJOIN DE 2 FUNCIONES NULL OJO
	if (rem_buffer == NULL)
		return (NULL);
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

	fd = open("e.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Opening file ERROR\n");
		return (1);
	}
	linea = get_next_line(fd);
	// printf("%s", linea);
	// free (linea);
	// linea = get_next_line(fd);
	// printf("%s", linea);
	// free (linea);
	// linea = get_next_line(fd);
	// printf("%s", linea);
	// free (linea);
	// linea = get_next_line(fd);
	while (linea != NULL)
	{
		printf("%s", linea);
		free (linea);
		linea = get_next_line(fd);
	}
	//
	if (close(fd) == -1)
	{
		printf("Closing file ERROR");
		return (1);
	}
	return (0);
}