/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 00:57:46 by zachamou          #+#    #+#             */
/*   Updated: 2023/12/26 12:12:52 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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

void	error_arg1(void)
{
	write(2, "\033[1;31m!! Not the 5 number of arguments :c !!\n033[0m\n", 46);
	write(2, "\033[1;32mExample: ./pipex infile cmd1 cmd2 outfile\033[0m\n",
		54);
	exit(EXIT_FAILURE);
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
