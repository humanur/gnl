/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsagman <amsagman@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:30:33 by amsagman          #+#    #+#             */
/*   Updated: 2024/12/21 01:47:26 by amsagman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static char	*copy_backup(char *backup, char *buffer)
{
	char	*res;
	size_t	lbackup;
	size_t	lbuffer;

	res = 0;
	lbackup = 0;
	lbuffer = 0;
	while (backup && backup[lbackup] != '\0')
		lbackup++;
	while (buffer[lbuffer] != '\0')
		lbuffer++;
	if (!backup && buffer)
	{
		res = ft_substr(buffer, 0, lbuffer);
		if (!res)
			return (NULL);
		return (res);
	}
	res = ft_strjoin(backup, buffer);
	free_backup(&backup, 0);
	return (res);
}

static int	check_newline(char *s)
{
	if (!s)
		return (0);
	if (ft_strchr(s, '\n') != NULL)
		return (1);
	return (0);
}

static char	*get_first_line(char *backup)
{
	char	*nl;
	size_t	i;

	i = 0;
	if (!backup)
		return (0);
	while (backup[i] != '\n')
		i++;
	nl = malloc(i + 2);
	if (!nl)
		return (0);
	ft_strlcpy(nl, backup, i + 2);
	return (nl);
}

static char	*update_backup(char *backup)
{
	size_t	i;
	size_t	len;
	char	*res;

	i = 0;
	len = 0;
	if (!backup)
		return (NULL);
	while (backup[i] != '\n')
		i++;
	if (backup[i + 1] == '\0')
		return (free_backup(&backup, 0));
	while (backup[i + 1 + len] != '\0')
		len++;
	res = ft_substr(backup, i + 1, len);
	if (!res)
	{
		free_backup(&backup, 0);
		return (NULL);
	}
	free_backup(&backup, 0);
	return (res);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		readed;
	static char	*backup = NULL;
	char		*nl;

	nl = NULL;
	readed = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_backup(&backup, 0));
	while (readed > 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if ((readed <= 0 && !backup) || readed == -1)
			return (free_backup(&backup, 0));
		buffer[readed] = '\0';
		backup = copy_backup(backup, buffer);
		if (check_newline(backup))
		{
			nl = get_first_line(backup);
			if (!nl)
				return (free_backup(&backup, 0));
			return (backup = update_backup(backup), nl);
		}
	}
	return (free_backup(&backup, 1));
}
