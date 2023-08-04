NAME	= so_long

SRCSDIR	= src/

SRCS = main.c create_map.c error.c checker_map.c key_hook.c so_long_utils.c movement_player.c map_search_all.c

OBJS	= $(addprefix $(SRCSDIR), $(SRCS:.c=.o))

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
MLXFRAGS = -lX11 -lXext -lm

LIBFTDIR	= libft/
LIBFTNAME	= libft.a
MLXDIR		= minilibx/
MLXNAME		= libmlx.a

all:$(NAME)

$(NAME):$(OBJS)
	$(MAKE) -C $(LIBFTDIR)
#	$(MAKE) -C $(MLXDIR)
	$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJS) -L$(LIBFTDIR) -lft #-L$(MLXDIR) -lmlx $(MLXFRAGS)

.c.o:
	$(CC) $(CFLAGS) -Imlx -c $< -o $(<:.c=.o)

#$(MLXDIR)$(MLXNAME):
#	$(MAKE) -C $(MLXDIR)

$(LIBFTDIR)$(LIBFTNAME):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFTDIR) clean
#	$(MAKE) -C $(MLXDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
#	$(MAKE) -C $(MLXDIR) fclean

re: fclean all
