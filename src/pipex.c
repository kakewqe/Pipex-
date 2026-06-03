/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:02:50 by zachamou          #+#    #+#             */
/*   Updated: 2023/12/28 19:07:28 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*find_path(char *cmd, char **ev)
{
	char	**allpaths;
	char	*exe;
	int		i;

	i = 0;
	while (ev[i])
	{
		if (ft_strnstr(ev[i], "PATH=", 5) != NULL)
			break ;
		i++;
	}
	allpaths = ft_split((ev[i] + 5), ':');
	i = 0;
	while (allpaths[i])
	{
		exe = build_executable_path(cmd, allpaths[i]);
		if (exe != NULL)
		{
			ft_clear_tab(allpaths);
			return (exe);
		}
		i++;
	}
	ft_clear_tab(allpaths);
	return (NULL);
}

void	exe(char **ev, char *av)
{
	char	**cmd;
	char	*cmd_exe;

	cmd = ft_split(av, ' ');
	cmd_exe = find_path(cmd[0], ev);
	if (cmd_exe == NULL)
	{
		perror("pipex: command not found");
		ft_putendl_fd(cmd[0], 2);
		ft_clear_tab(cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd_exe, cmd, ev) == -1)
	{
		perror("pipex: execution error");
		ft_putendl_fd(cmd[0], 2);
		ft_clear_tab(cmd);
		free(cmd_exe);
		exit(EXIT_FAILURE);
	}
}

void	parent_pro(char **ev, char **av, int *fd)
{
	int	outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror("pipex: permission denied error");
		exit(EXIT_FAILURE);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	close(outfile);
	exe(ev, av[3]);
}

void	child_pro(char **ev, char **av, int *fd)
{
	int	infile;

	if (access(av[1], F_OK) != 0)
	{
		perror("pipex: no such file or directory error");
		exit(EXIT_FAILURE);
	}
	infile = open(av[1], O_RDONLY);
	if (infile == -1)
	{
		perror("pipex: permission denied error");
		exit(EXIT_FAILURE);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(infile);
	exe(ev, av[2]);
}

int	main(int ac, char **av, char **emv)
{
	int		fd[2];
	pid_t	pid;

	if (ac != 5)
		error_arg1();
	if (pipe(fd) == -1)
	{
		perror("pipex: pipe error");
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("pipex: fork error");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		child_pro(emv, av, fd);
	waitpid(pid, NULL, 0);
	parent_pro(emv, av, fd);
	return (EXIT_SUCCESS);
}
