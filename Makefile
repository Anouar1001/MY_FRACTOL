SRCS = main.c tools.c read_args.c tools3.c tricorn.c
OBJS = ${SRCS:.c=.o}
NAME = fractol
FC = ar r
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
MLX = minilibx-linux/libmlx_Linux.a

all: ${NAME}

${NAME}: ${OBJS} ${MLX}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${MLX} -lXext -lX11 -o ${NAME}

%.o: %.c fractol.h minilibx-linux/mlx.h
	@${CC} ${CFLAGS} -c $< -o $@

${MLX}:
	@${MAKE} -C ./minilibx-linux

clean:
	@${RM} ${OBJS}

fclean: clean
	@${MAKE} -C minilibx-linux clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re