/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldel-rio <ldel-rio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:43:17 by ldel-rio          #+#    #+#             */
/*   Updated: 2024/02/08 20:46:55 by ldel-rio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_add(int fd, char *full_line)
{
	char	*buff;
	int		readed;

	readed = 1;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (!ft_strchr(full_line, '\n') && readed != 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
			return (NULL);
		if (full_line == NULL && readed == 0)
		{
			free(buff);
			return (NULL);
		}
		if (!full_line)
			full_line = malloc(1);
		buff[readed] = '\0';
		full_line = ft_strjoin(full_line, buff);
		free(buff);
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	}
	free(buff);
	return (full_line);
}

char	*extract_line(char *full_line)
{
	int		i;
	char	*extracted;

	i = 0;
	while (full_line[i] != '\0' && full_line[i] != '\n')
		i ++;
	extracted = ft_substr(full_line, 0, i);
	if (full_line[i] == '\n')
	{
		extracted[i] = '\n';
		i ++;
	}
	extracted[i] = '\0';
	return (extracted);
}

char	*next_line(char *full_line)
{
	int		i;
	int		j;
	char	*new_full_line;

	i = 0;
	j = ft_strlen(full_line);
	while (full_line[i] != '\0' && full_line[i] != '\n')
		i ++;
	new_full_line = ft_substr(full_line, i + 1, (j - i));
	free(full_line);
	full_line = NULL;
	return (new_full_line);
}

char	*get_next_line(int fd)
{
	static char	*full_line;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!full_line)
		full_line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	full_line = read_and_add(fd, full_line);
	if (full_line == NULL)
	{
		free(full_line);
		return (NULL);
	}
	line = extract_line(full_line);
	full_line = next_line(full_line);
	return (line);
}

int	main()
{
	char	*line;
	int		i;
	int		fd1;

	fd1 = open("example.txt", O_RDONLY);
	i = 1;
	while (i < 10)
	{
		line = get_next_line(fd1);
		if (line == NULL)
			break ;
		printf("[%d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}