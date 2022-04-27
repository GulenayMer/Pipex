# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 14:58:08 by mgulenay          #+#    #+#              #
#    Updated: 2022/04/22 16:30:09 by mgulenay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	pipex

CC 		= 	gcc

CFLAGS 	= 	-Wall -Wextra -Werror

SRCS 	=	pipex.c \

SRC_OBJS	=	$(SRCS:%.c=%.o)

RM          =	rm -f

$(NAME): $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC_OBJS)

all : $(NAME)

clean:
		$(RM) $(SRC_OBJS)
		
fclean:		clean
				$(RM) $(NAME)

re: 		fclean all

.PHONY: all clean fclean re
