NAME		=	cub3d

CC		=	cc

CFLAGS		=	-Wall -Werror -Wextra

SRC		=	start.c init.c utils.c exit_window.c player_init.c info_read.c	\
			key_press_release.c  game_loop.c minimap.c map_create.c		\
			raycasting.c player_move.c raycasting_draw.c get_next_line.c	\
			minimap_player_wg.c utils_alloc_and_free.c check_data.c		\
			info_read_utils.c info_read2.c utils2.c utils_alloc_and_free2.c

INCLUDE		=	-L$(LIBDIR)/Libft -lft -L/usr/include -L$(LIBDIR)/mlx_linux -lmlx_Linux -L/usr/lib -I$(LIBDIR)/mlx_linux -lXext -lX11 -lm #-lz

HEADER	 	=	cub3d.h

OBJDIR		=	obj

LIBDIR		=	libs

SRCDIR		=	src

OBJS		=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

SRCS		=	$(addprefix $(SRCDIR)/, $(SRC))

VPATH		=	header/ src/ obj/ include/ /libs

all :  create_dir libft mlx_linux $(NAME)

mlx_linux:
	make -C $(LIBDIR)/mlx_linux

libft:
	cd $(LIBDIR)/Libft && $(MAKE)

$(NAME) :	$(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)


create_dir:
	@mkdir -p $(OBJDIR)

clean :
	cd $(LIBDIR)/Libft && make $@
	rm -rf $(OBJS)

fclean : clean
	cd $(LIBDIR)/Libft && make $@
	rm -rf $(NAME)

re : fclean all

.PHONY: all libft create_dir clean fclean re mlx_linux

obj/%.o: src/%.c
	$(CC) -I/usr/include -Imlx_linux -O3 $(CFLAGS) -c $< -o $@
