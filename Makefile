# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zack <zack@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/26 11:10:04 by zachamou          #+#    #+#              #
#    Updated: 2023/12/28 12:18:59 by zack             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Werror -Wall -Wextra 

RM = rm -rf

SRCS = 	src/pipex.c\
		src/utils.c\
		libft/libft.a\

SRC_BONUS =	src_bns/pipex_bonus.c\
			src_bns/utils_bonus.c\
			src_bns/erro.c\
			libft/libft.a\

$(NAME) :
	make all -C libft
	cc $(CFLAGS) $(SRCS) -o $(NAME)

bonus : clean
	make all -C libft
	cc $(CFLAGS) $(SRC_BONUS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) $(NAME)
	make clean -C libft

re : fclean all