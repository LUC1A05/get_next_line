/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldel-rio <ldel-rio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:43:11 by ldel-rio          #+#    #+#             */
/*   Updated: 2024/02/08 17:03:25 by ldel-rio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

char		*get_next_line(int fd);
char		*extract_line(char *full_line);
char		*next_line(char *full_line);
char		*ft_substr(char const *s, int start, int len);
char		*read_and_add(int fd, char *full_line, int readed);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
