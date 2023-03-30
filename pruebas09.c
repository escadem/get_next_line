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

char	*ft_initializing(int fd, char *buffer, int *nl_pos, int *byt_read)
{
	char	*str;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	*nl_pos = ft_check_nl(buffer);
	if (*nl_pos)
	
	str = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
	{
		free (buffer);
		return (NULL);
	}
	str[0] = '\0';
	*byt_read = read(fd, str, BUFFER_SIZE);
	str[*byt_read] = '\0';
	// if (*byt_read != BUFFER_SIZE)
	// 	*byt_read = ft_strlen(str);
	if (!*byt_read)
		return (NULL);
	return (str);
}

char	*ft_clean_temp(char *t_buffer, int nl_pos, int byt_read)
{
	char	*aux;
	int		i;

	i = byt_read - 1;
	if (!nl_pos && byt_read < BUFFER_SIZE)
	{
		while (++i < BUFFER_SIZE)
			t_buffer[i] = '\0';
	}
	aux = (char *)malloc((nl_pos + 1) * sizeof(char));
	if (!aux)
	{
		free (t_buffer);
		return (NULL);
	}
	i = -1;
	while (++i < nl_pos)
		aux[i] = t_buffer[i];
	aux[nl_pos] = '\0';
	return (aux);
}

char	*ft_get_line(char *p_buffer, char *t_buffer, int *nl_pos, int *byt_read)
{
	char	*temp;
	char	*line;

	if (*byt_read == -1)
	{
		free (t_buffer);
		free (p_buffer);
		return (0);
	}
	if (!(*nl_pos) && !(*byt_read))
	{
		free (t_buffer);
		return (p_buffer);
	}
	temp = ft_clean_temp(t_buffer, *nl_pos, *byt_read);
	line = ft_strjoin(p_buffer, temp);
	free (temp);
	return (line);
}


char	*ft_clean_perm(char *p_buff, char *t_buff, int *nl_pos)
{
	char	*tmp;
	int		i;

	if (!(*nl_pos))
		return (NULL);
	i = 0;
	tmp = (char *)malloc((BUFFER_SIZE - *nl_pos) * sizeof(char));
	if (!tmp)
	{
		free(t_buff);
		free(p_buff);
		return (NULL);
	}
	while ((i + *nl_pos) < BUFFER_SIZE)
	{
		tmp[i] = t_buff[i + *nl_pos];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}


char	*get_next_line(int fd)
{
	static char	*perm_buffer;
	char		*temp_buffer;
	char		*line;
	int			byt_read;
	int			nl_pos;

	temp_buffer = ft_initializing(fd, perm_buffer, &nl_pos, &byt_read);
	if (perm_buffer == NULL || nl_pos == 0)
		// perm_buffer = ft_read_file(fd, perm_buffer, &nl_pos, &byt_read);
		perm_buffer = ft_strjoin(perm_buffer, temp_buffer);
	if (perm_buffer == NULL)
		return (NULL);
	while (!nl_pos && byt_read == BUFFER_SIZE)
	{
		byt_read = read(fd, temp_buffer, BUFFER_SIZE);
		nl_pos = ft_check_nl(temp_buffer);
		perm_buffer = ft_strjoin(perm_buffer, temp_buffer);
	}
	line = ft_get_line(perm_buffer, temp_buffer, &nl_pos, &byt_read);
	perm_buffer = ft_clean_perm(perm_buffer, temp_buffer, &nl_pos);
	free (temp_buffer);
	return (line);
}

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

	if (close(fd) == -1)
	{
		printf("Closing file ERROR");
		return (1);
	}
	return (0);
}