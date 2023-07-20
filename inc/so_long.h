#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
//# include "../minilibx/mlx.h"
//# include "../minilibx/mlx_int.h"
# include <mlx.h>
# include <fcntl.h>

//map_image
# define P_IMG_PLAYER  "textures/player.xpm"
# define P_IMG_GRASS  "textures/grass.xpm"
# define P_IMG_WOOD  "textures/wood.xpm"
# define P_IMG_DOOR  "textures/door.xpm"
# define P_IMG_ITEM  "textures/item.xpm"

//keycode
# define X_ESC 65307
# define X_UP 65362
# define X_DOWN 65364
# define X_RIGHT 65363
# define X_LEFT 65361

//imac keycode
# define ESC 53
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define W 13
# define A 0
# define S 1
# define D 2

typedef struct s_player
{
	int	p_x;
	int	p_y;
}	t_player;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		pixel;
	int		len;
	int		end;
}	t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
	int		map_x;
	int		map_y;
	char	**map;
}	t_vars;

int		put_window(char **argv);
void	create_map(t_vars vars, char **argv);
void	error(void);
void	error_map(int fd);
size_t	my_strnlen(const char *str);
void	checker_map(char **argv, t_vars vars);
void	hook(t_vars *vars);

//utils
char	*my_strjoin(char const *s1, char const *s2);
size_t	my_strchrlen(const char *s, int c);

#endif
