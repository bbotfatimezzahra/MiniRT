# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbbot <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/23 15:03:44 by fbbot             #+#    #+#              #
#    Updated: 2025/02/23 15:14:07 by fbbot            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt
CFILES = main.c tuples.c tuples_utils.c canvas.c clean.c matrix.c camera.c\
	 transform.c ray.c intersect.c sphere.c vector.c light.c ft_split.c\
	 material.c parse.c cylinder.c atod.c scene.c plane.c str_utils.c\
	 Get_next_line/get_next_line_utils.c Get_next_line/get_next_line.c 
OFILES = $(CFILES:%.c=%.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3
LFLAGS	= -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
INC = -I/usr/include -Imlx_linux -O3

.PHONY: all clean fclean re

.SECONDARY : $(OFILES)

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OFILES) 
	$(CC) $(CFLAGS) $(OFILES) -Lmlx_linux -lmlx_Linux $(LFLAGS) -o $(NAME)  

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
