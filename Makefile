# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 21:52:21 by soooh             #+#    #+#              #
#    Updated: 2021/06/25 20:20:46 by soooh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex

CC				= gcc
RM				= rm -rf
SRCS			= ./srcs/pipex.c\
					./srcs/px_redirection.c\
					./srcs/px_pipe.c\
					./srcs/px_execve.c\
					./srcs/px_utils.c\
					./srcs/ft_split.c

SRCS_B			= ./bonus/pipex_bonus.c\
					./bonus/px_redirection_bonus.c\
					./bonus/px_pipe_bonus.c\
					./bonus/px_execve_bonus.c\
					./bonus/px_utils_bonus.c\
					./bonus/px_utils_bonus2.c\
					./bonus/ft_split.c\
					./bonus/gnl/get_next_line.c\
					./bonus/gnl/get_next_line_utils.c

OBJS			= $(SRCS:.c=.o)
OBJS_B			= $(SRCS_B:.c=.o)
OUTFILE			= out
CFLAGS			= -Wall -Wextra -Werror
#CFLAGS    		= -g3 -fsanitize=address

INC_LINK 		= -I./srcs 

all: $(NAME)

bonus:			re
	@$(MAKE) fclean -C ./bonus
	@$(MAKE) -C ./bonus
	@cp ./bonus/pipex_bonus ./pipex_bonus

$(NAME):		$(OBJS)
	@$(CC) -o $(NAME) $(CFLAGS) $(INC_LINK) $(OBJS)

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_B)
	@$(RM) $(OUTFILE)

fclean: clean
	@$(RM) $(NAME)
	@if [ -f ./pipex_bonus ]; then $(RM) ./pipex_bonus; fi;
	@if [ -f ./bonus/pipex_bonus ]; then $(RM) ./bonus/pipex_bonus; fi;

re:				fclean all

.PHONY:			all clean fclean re bonus