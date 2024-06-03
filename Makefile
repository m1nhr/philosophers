# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 15:10:19 by marecarraya       #+#    #+#              #
#    Updated: 2023/05/30 11:49:49 by rmarecar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	gcc

FLAGS	=	-Wall -Werror -Wextra -pthread -g -I/include/philo.h

C_FILE	=	init.c philo.c threads.c utils.c finish.c

SRC_DIR	=	./srcs/

INC_DIR	=	./include/

SRC	=	$(addprefix $(SRC_DIR),$(C_FILE))

OBJ		=	$(SRC:.c=.o)

.c.o:
		$(CC) $(FLAGS) -I$(INC_DIR) -c $< -o $@

all: $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) $(FLAGS) -I$(INC_DIR) -o $(NAME)

clean:
		@rm -f $(OBJ)

fclean:	clean
		@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re