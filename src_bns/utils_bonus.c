/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:10:24 by zachamou          #+#    #+#             */
/*   Updated: 2023/12/28 21:03:30 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#define BUFFER_SIZE 100000

void	parent_process(int fd[])
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	wait(NULL);
}

int	gnl(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	while (1)
	{
		r = read(0, &c, 1);
		if (r > 0 && c != '\n' && c != '\0')
			buffer[i++] = c;
		else
		{
			buffer[i] = '\n';
			buffer[++i] = '\0';
			*line = buffer;
			if (r > 0 || i > 0)
				return (1);
			else
				return (r);
		}
	}
}

void	ft_clear_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*build_executable_path(char *cmd, char *path)
{
	char	*part_path;
	char	*exe;

	part_path = ft_strjoin(path, "/");
	exe = ft_strjoin(part_path, cmd);
	free(part_path);
	if (access(exe, F_OK | X_OK) == 0)
		return (exe);
	free(exe);
	return (NULL);
}
