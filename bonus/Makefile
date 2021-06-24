# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 21:52:21 by soooh             #+#    #+#              #
#    Updated: 2021/06/25 02:12:54 by soooh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex_bonus

CC				= gcc
RM				= rm -rf
SRCS			= ./pipex_bonus.c\
					./px_redirection_bonus.c\
					./px_pipe_bonus.c\
					./px_execve_bonus.c\
					./px_utils_bonus.c\
					./ft_split.c

OBJS			= $(SRCS:.c=.o)
OUTFILE			= out
CFLAGS			= -Wall -Wextra -Werror
#CFLAGS    		= -g3 -fsanitize=address

INC_LINK 		=

all: $(NAME)

$(NAME):		$(OBJS)
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJS)

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OUTFILE)

fclean: clean
	@$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re