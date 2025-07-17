/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:44:13 by lnul-hak          #+#    #+#             */
/*   Updated: 2024/04/03 14:38:59 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*updated(char *old_buffer, char *new_buffer)
{
	char	*temp;

	temp = ft_strjoin(old_buffer, new_buffer);
	free(old_buffer);
	return (temp);
}

static char	*leftovers(char *buffer)
{	
	int		i;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	line = ft_substr(buffer, i + 1, ft_strlen(buffer));
	free(buffer);
	return (line);
}

static char	*nl_found(char *buffer)
{	
	int		i;
	char	*line;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_substr(buffer, 0, i);
	if (buffer[i] == '\n')
		line = updated(line, "\n");
	return (line);
}

static char	*read_file(int fd, char *buffer)
{		
	char	*new_read;
	int		bytes_read;

	new_read = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (new_read == NULL)
		return (NULL);
	bytes_read = 42;
	while (!ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, new_read, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		else if (bytes_read == -1)
		{	
			free(new_read);
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		new_read[bytes_read] = '\0';
		buffer = updated(buffer, new_read);
	}
	free(new_read);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*line_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (line_buffer == NULL)
	{
		line_buffer = (char *)malloc(sizeof(char) * 1);
		line_buffer[0] = '\0';
	}
	if (!ft_strchr(line_buffer, '\n'))
	{
		line_buffer = read_file(fd, line_buffer);
		if (line_buffer == NULL)
		{
			free(line_buffer);
			line_buffer = NULL;
			return (NULL);
		}
	}
	line = nl_found(line_buffer);
	line_buffer = leftovers(line_buffer);
	return (line);
}
