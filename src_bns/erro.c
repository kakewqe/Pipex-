/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erro.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:47:03 by zachamou          #+#    #+#             */
/*   Updated: 2023/12/28 19:31:28 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	error_arg(void)
{
	write(2, "\033[1;31m!! we need more than 5 arguments :c !!\n\033[0m\n", 49);
	write(2, "\033[1;32mExample: ./Here_doc cmd1 cmd2 outfile\033[0m\n", 50);
	write(2,
		"\033[1;32mExample 2: ./pipex infile cmd1 cmd2 cmd3 ... outfile\033[0m\n",
		65);
	exit(EXIT_FAILURE);
}

void	error(void)
{
	perror("Pipe or Fork or ARG");
	exit(EXIT_FAILURE);
}
