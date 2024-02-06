/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldel-rio <ldel-rio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:43:17 by ldel-rio          #+#    #+#             */
/*   Updated: 2024/02/06 17:16:16 by ldel-rio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main()
{
	int		fd;
	char	*line;

	fd = open("example.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s\n", line);
	while ((line = get_next_line(fd)) != NULL)
/* 	{
		printf("%s\n", line);
		free(line);
	} */
	close(fd);
	return (0);
}

char	*read_and_add(int fd, char *full_line, int readed)
{
	char	*buff;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (!ft_strchr(buff, '\n') && readed != 0)
	{
		if (buff == NULL)
			return (NULL);
		readed = read(fd, buff, BUFFER_SIZE);
		if (full_line == NULL && readed == 0)
		{
			free(buff);
			return (NULL);
		}
		buff[readed] = '\0';
		full_line = ft_strjoin(full_line, buff);
		free(buff);
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	}
	free(buff);
	return (full_line);
}

char	*extract_line(char **full_line)
{
	int		i;
	int		j;
	char	*temp;
	char	*extracted;

	i = 0;
	j = ft_strlen(*full_line);
	while (full_line[0][i] != '\n')
		i ++;
	extracted = ft_substr(full_line[0], 0, i);
	temp = malloc(sizeof(char) * ft_strlen(full_line[0]));
	ft_strlcpy(full_line[0], temp, ft_strlen(full_line[0]));
	free(full_line[0]);
	*full_line = temp;
	return (extracted);
}

char	*get_next_line(int fd)
{
	static char	*full_line = NULL;
	char		*line;
	int			readed;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readed = 1;
	if (!full_line)
		full_line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	full_line = read_and_add(fd, full_line, readed);
	if (full_line == NULL)
		return (NULL);
	line = extract_line(&full_line);
	return (line);
}
