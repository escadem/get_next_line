#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BUFFER_SIZE 1

/// @brief standard string lenthe function
/// @param s String which length must be calculated
/// @return the length of the string
size_t	ft_strlen(const char *s)
{
	size_t	i;

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
	// printf("len_s1 = %d\n", len_s1);
	// printf("len_s2 = %d\n", len_s2);

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

/// @brief  splits the buffer in 2: the line and a clean new buffer
/// @param source string to be splitted
/// @param nl_pos position of the  '\\n'
/// @return the line including '\\n'
char	*ft_db_line(char *source, int nl_pos)
{
	char	*line;
	int		i;

	i = 0;
	// printf("nl_pos = %d\n", nl_pos);
	// printf("byt_read = %d\n", len_source);
	line = malloc((nl_pos + 1) * sizeof(char));
	if (!line)
	{
		free (source);
		return (NULL);
	}
	// printf("entra el ft_cleaner\n");
	while (i < nl_pos)
	{
		line[i] = source[i];
		i++;
	}
	line[i] = '\0';
	// printf("line: %s\n", line);
	i = 0;
	// printf("i: %d\n", i);
	// printf("source[i=%d + nl_pos=%d + 1]=%c\n", i, nl_pos, source[i+nl_pos]);
	return (line);
}

char	*ft_clean_str(char *source, int nl_pos)
{
	char	*temp;
	int		i;
	int		len_source;

	i = 0;
	len_source = ft_strlen(source);
	// printf("nl_pos = %d\n", nl_pos);
	// printf("byt_read = %d\n", len_source);
	temp = malloc((len_source - nl_pos + 1) * sizeof(char));
	i = 0;
	// printf("i: %d\n", i);
	// printf("source[i=%d + nl_pos=%d + 1]=%c\n", i, nl_pos, source[i+nl_pos]);
	
	while (source[i + nl_pos] != '\0')
	{
		temp[i] = source[i + nl_pos];
		i++;
		// j++;
	}
	temp[i] = '\0';
	// printf("temp: %s\n", temp);
	free (source);
	// source = temp;
	// printf("source: %s\n", source);
	// return (source);
	return (temp);
}

// /// @brief when there is no '\\n' in the string it must be
// ///        increased in +BUFFER_SIZE characters 
// /// @param fd file descriptor
// /// @param membuff String to be increased
// /// @param byt_read pointer. While condition parameter in GNL function
// /// @return points the new created string (its address)
// char	*ft_expandbuffer(int fd, char *membuff, int *byt_read)
// {
// 	char	buffer[BUFFER_SIZE + 1];
// 	char	*temp;

// 	temp = ft_strjoin(membuff, buffer);
// 	// free (membuff);
// 	return (temp);
// }

/// @brief project main function
/// @param fd file descriptor
/// @return line
char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*membuff;
	char		*temp;
	int			byt_read;
	int			nl_pos;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
		return (NULL);

	nl_pos = ft_check_nl(membuff);
	// printf("nl_pos inicio = %d\n", nl_pos);
	byt_read = 1;
	// printf("entra en get_next_line\n");
	// printf("membuff: %s\n", membuff);
	// if (nl_pos)
	// {
	// 	temp = ft_db_line(membuff, nl_pos);
	// 	membuff = ft_clean_str(membuff, nl_pos);
	// 	return (temp);
	// }
	// printf("byt_read: %d\n", byt_read);
	while (byt_read)
	{
		// printf("entra en bucle\n");
		if(!nl_pos)
		{
			byt_read = read(fd, buffer, BUFFER_SIZE);
			if (byt_read == -1)
			return (NULL);
			if (byt_read == 0)
			return (membuff);
			// printf("]]]]byt_read: %d\n", byt_read);
			// buffer[BUFFER_SIZE] = '\0';
			buffer[byt_read] = '\0';
			// printf("pasa lectura de memoria\n");
			membuff = ft_strjoin(membuff, buffer);
			// printf("pasa memebuff\n");
			nl_pos = ft_check_nl(membuff);
			// printf("membuff: %s\n", membuff);
			// printf("nl_pos: %d\n", nl_pos);	
		}
		if (nl_pos)
		{
			temp = ft_db_line(membuff, nl_pos);
			membuff = ft_clean_str(membuff, nl_pos);
			return (temp);
		}
			// return (ft_db_line(membuff, nl_pos));
	}
	return (NULL);
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
	printf("%s", linea);
	free (linea);
	linea = get_next_line(fd);
	printf("%s", linea);
	free (linea);
	linea = get_next_line(fd);
	printf("%s", linea);
	free (linea);
	// linea = get_next_line(fd);
	// while (linea != NULL)
	// {
	// 	printf("%s", linea);
	// 	free (linea);
	// 	linea = get_next_line(fd);
	// }

	if (close(fd) == -1)
	{
		printf("Closing file ERROR");
		return (1);
	}
	return (0);
}