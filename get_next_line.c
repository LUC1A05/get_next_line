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

int main() {
    // Example usage
    int fd = open("example.txt", O_RDONLY);
    char *line = get_next_line(fd);
    
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
    return (0);
}

void	read_and_add(int fd, char *full_line, int readed)
{
	char	*buff;

	while (!ft_strchr(buff, '\n') && readed != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL)
			return;
		readed = read(fd, buff, BUFFER_SIZE);
		if (full_line == NULL && readed == 0)
		{
			free(buff);
			return;
		}
		buff[readed] = '\0';
		full_line = ft_strjoin(full_line, buff);
		free(buff);
	}
}

void extract_line(char *full_line, char *line)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = ft_strlen(full_line);
	while(!ft_strchr(full_line, '\0'))
		i ++;
	line = ft_substr(full_line, 0, i);
	temp = full_line;
	free(full_line);
	full_line = ft_substr(temp, i, (j-i));
}

char	*get_next_line(int fd)
{
	static char	*full_line;
	char		*line;
	int			readed;

	if (fd < 0 || read(fd, &line, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readed = 1;
	line = NULL;
	read_and_add(fd, full_line, readed);
	if (full_line == NULL)
		return (NULL);
	extract_line(full_line, line);
	return (line);
}