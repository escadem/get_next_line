/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescat-l <eescat-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:37:34 by eescat-l          #+#    #+#             */
/*   Updated: 2023/04/01 09:40:58 by eescat-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// PROTOTYPES DEFINITION get_next_line_utils
int		ft_strlen(const char *s);
char	*ft_calloc_str(size_t count);
int		ft_check_nl(char *string);
char	*ft_strjoin(char *s1, char *s2);

// PROTOTYPES DEFINITION get_next_line
char	*ft_initializing(int fd, char *rembuffer, int *nl_pos, int *byt_read);
char	*ft_get_line(char *r_buffer, int *byt_read);
char	*ft_clean_rem(char *rbuffer, int *nl_pos);
char	*get_next_line(int fd);


#endif