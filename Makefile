# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 21:52:21 by soooh             #+#    #+#              #
#    Updated: 2021/06/21 22:18:08 by soooh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex

CC				= gcc
RM				= rm -rf
SRCS			= ./srcs/pipex.c
OBJS			= $(SRCS:.c=.o)

CFLAGS			= -Wall -Wextra -Werror
#CFLAGS    		= -g3 -fsanitize=address

INC_LINK 		= -I./srcs


all: $(NAME)

$(NAME):		$(OBJS)
	@$(CC) -o $(NAME) $(CFLAGS) $(INC_LINK) $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean:
	@$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re libft bonus