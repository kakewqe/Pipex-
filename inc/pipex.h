/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:42:14 by zachamou          #+#    #+#             */
/*   Updated: 2023/12/28 21:04:21 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

//mandatory
void	ft_clear_tab(char **tab);
char	*build_executable_path(char *cmd, char *path);
void	exe(char **ev, char *av);

//bonus
int		gnl(char **line);
void	do_pipe(char **av, char **ev);
void	parent_process(int fd[]);
int		open_file(void);

//error
void	error_arg1(void);
void	error_arg(void);
void	error(void);

#endif
