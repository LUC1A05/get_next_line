/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldel-rio <ldel-rio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:43:17 by ldel-rio          #+#    #+#             */
/*   Updated: 2024/01/24 17:12:51 by ldel-rio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return(temp);
}
char	*clear_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == NULL)
	{
		free(buffer);
		return (NULL);
	}
	line = malloc((sizeof(char)) * (ft_strlen(buffer) - i + 1));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return(line);
}

static char	*new_line(char *bassin_buffer)
{
	char	*line;
	char	*str;
	int		len;

	str = ft_strchr(bassin_buffer, '\n');
	len = (bassin_buffer - str) + 1;
	line = ft_substr(bassin_buffer, 0, len);
	if (line == NULL)
		return (NULL);
	return (line);
}

static char	*read_from_file(char *basin_buffer, int fd)
{
	int			bytes_read;
	char		*cup_buffer;

	bytes_read = 1;
	cup_buffer = malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (cup_buffer == NULL)
		return (ft_free());
	bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free (cup_buffer);
		return (NULL);
	}
	return (cup_buffer);
}

char	*get_next_line(int fd)
{
	static char	*basin_buffer;
	char		*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	basin_buffer = read_file(basin_buffer, fd);
	if (basin_buffer == NULL)
		return (NULL);
	line = new_line(basin_buffer);
	basin_buffer = clear_buffer(basin_buffer);
	return (line);
}
