#include "cub3d.h"
#include <math.h>

int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	rotate_player(t_player *p, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
	p->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
	p->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
}

int	mouse_move(int x, int y, t_game *game)
{
	static int	old_x = -1;
	int			dx;
	double		rot;

	(void)y;
	if (old_x == -1)
	{
		old_x = WIN_WIDTH / 2;
		mlx_mouse_move(game->mlx.mlx,
			game->mlx.win,
			WIN_WIDTH / 2,
			WIN_HEIGHT / 2);
		return (0);
	}
	dx = x - old_x;
	if (ft_abs(dx) <= 1)
		return (0);
	rot = dx * MOUSE_SENSITIVITY;
	rotate_player(&game->player, rot);
	mlx_mouse_move(game->mlx.mlx,
		game->mlx.win,
		WIN_WIDTH / 2,
		WIN_HEIGHT / 2);
	old_x = WIN_WIDTH / 2;
	return (0);
}
