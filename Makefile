NAME = minirt

CFILES = main.c tuples.c tuples_utils.c canvas.c clean.c matrix.c camera.c\
	 transform.c ray.c intersect_obj.c intersect_world.c sphere.c compute_vectors.c light.c ft_split.c\
	 material.c parse.c cylinder.c atod.c scene.c plane.c str_utils.c\
	 Get_next_line/get_next_line_utils.c Get_next_line/get_next_line.c paint_pixel.c\
	 reflect_and_refract.c patterns.c render_scene.c parse_utils.c print.c cone.c\
	 rodrigues_formula.c\

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
