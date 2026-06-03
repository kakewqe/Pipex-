/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:10:35 by zachamou          #+#    #+#             */
/*   Updated: 2023/12/28 21:25:39 by zachamou         ###   ########.fr       */
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
	if (cmd == NULL)
	{
		perror("ft_split");
		exit(EXIT_FAILURE);
	}
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

void	do_pipe(char **av, char **ev)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error_arg();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exe(ev, av[0]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	here_doc(char *limiter, int ac)
{
	int		fd[2];
	pid_t	pid;
	char	*line;

	if (ac > 6 || pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		while (gnl(&line) > 0)
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			{
				free(line);
				exit(EXIT_SUCCESS);
			}
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
		close(fd[1]);
	}
	parent_process(fd);
}

int	main(int ac, char **av, char **ev)
{
	int	in;
	int	out;
	int	i;

	if (ac < 5)
		error_arg();
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		i = 3;
		out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		here_doc(av[2], ac);
	}
	else
	{
		i = 2;
		out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		in = open(av[1], O_RDONLY);
		dup2(in, 0);
	}
	while (i < ac - 2)
		do_pipe(av + i++, ev);
	dup2(out, 1);
	exe(ev, av[ac - 2]);
	return (0);
}
