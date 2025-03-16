NAME = minirt

CFILES = main.c\
	utils/tuples.c utils/clean.c utils/matrix.c  utils/rodrigues_formula.c\
	utils/Get_next_line/get_next_line_utils.c utils/Get_next_line/get_next_line.c\
	utils/transform.c utils/ray.c utils/str_utils.c  utils/ft_split.c\
	utils/ft_atod.c utils/print.c utils/tuples_utils.c utils/matrix_utils.c\
	parsing/parse_utils.c parsing/cone.c parsing/light.c\
	parsing/cylinder.c  parsing/sphere.c parsing/material.c parsing/parse.c   parsing/plane.c \
	parsing/camera.c rendring/canvas.c\
	rendring/intersect_obj.c rendring/intersect_world.c rendring/compute_vectors.c\
	rendring/paint_pixel.c rendring/compute_light.c rendring/patterns.c rendring/render_scene.c\
	

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
