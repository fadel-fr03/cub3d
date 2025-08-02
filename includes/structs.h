#ifndef STRUCTS_H
# define STRUCTS_H

// Window dimensions
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

// Movement and rotation speed
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

// Texture dimensions
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

// Player structure
typedef struct s_player
{
	double	pos_x;		// Player X position
	double	pos_y;		// Player Y position
	double	dir_x;		// Direction vector X
	double	dir_y;		// Direction vector Y
	double	plane_x;	// Camera plane X
	double	plane_y;	// Camera plane Y
}	t_player;

// Texture structure
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_texture;

// Map data structure
typedef struct s_map
{
	char		**grid;		// 2D array of the map
	int			width;		// Map width
	int			height;		// Map height
	int			player_x;	// Initial player X position
	int			player_y;	// Initial player Y position
	char		player_dir;	// Initial player direction (N/S/E/W)
}	t_map;

// Color structure
typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

// Ray structure for raycasting calculations
typedef struct s_ray
{
	double	camera_x;		// X-coordinate in camera space
	double	ray_dir_x;		// Ray direction X
	double	ray_dir_y;		// Ray direction Y
	int		map_x;			// Current map square X
	int		map_y;			// Current map square Y
	double	side_dist_x;	// Distance to next X gridline
	double	side_dist_y;	// Distance to next Y gridline
	double	delta_dist_x;	// Distance between X gridlines
	double	delta_dist_y;	// Distance between Y gridlines
	double	perp_wall_dist;	// Perpendicular distance to wall
	int		step_x;			// Direction to step in X (-1 or 1)
	int		step_y;			// Direction to step in Y (-1 or 1)
	int		hit;			// Was a wall hit?
	int		side;			// NS or EW wall?
	int		line_height;	// Height of line to draw
	int		draw_start;		// Lowest pixel to fill
	int		draw_end;		// Highest pixel to fill
	double	wall_x;			// Where exactly the wall was hit
	int		tex_x;			// X coordinate on the texture
}	t_ray;

// MLX structure
typedef struct s_mlx
{
	void	*mlx;		// MLX pointer
	void	*win;		// Window pointer
	void	*img;		// Image pointer
	char	*addr;		// Image address
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

// Main game structure
typedef struct s_game
{
	t_mlx		mlx;			// MLX data
	t_player	player;			// Player data
	t_map		map;			// Map data
	t_texture	textures[4];	// NO, SO, WE, EA textures
	t_color		floor_color;	// Floor color
	t_color		ceiling_color;	// Ceiling color
	char		*texture_paths[4];	// Paths to texture files
	int			keys[6];		// Key states (W, A, S, D, LEFT, RIGHT)
}	t_game;

typedef struct s_mapline
{
	char				*line;
	struct s_mapline	*next;
}	t_mapline;

typedef struct s_parse_ctx
{
	int			map_started;
	t_mapline	*head;
	t_mapline	*tail;
	t_game		*game;
}	t_parse_ctx;

// Helper struct to pass map dimensions
typedef struct s_map_dims
{
	int	width;
	int	height;
}	t_map_dims;

// Helper struct to pass grid allocation context
typedef struct s_grid_context
{
	char		**grid;
	t_mapline	*lines;
	t_map_dims	dims;
}	t_grid_context;

typedef struct s_line_node
{
	char				*line;
	struct s_line_node	*next;
}	t_line_node;

void	free_line_list(t_line_node *head);

typedef struct s_line_data
{
	int			width;
	int			height;
	t_line_node	*head;
	t_line_node	*tail;
}	t_line_data;

// Helper struct for minimap coordinates
typedef struct s_minimap_coords
{
	int	start_x;
	int	start_y;
	int	map_x;
	int	map_y;
}	t_minimap_coords;

// Helper struct for border drawing
typedef struct s_border_data
{
	int	border_start_x;
	int	border_start_y;
	int	border_width;
	int	border_height;
}	t_border_data;

// Helper struct for rectangle drawing
typedef struct s_rect_data
{
	int	x;
	int	y;
	int	size;
	int	color;
}	t_rect_data;

// Key codes (adjust based on your system)
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

// Key array indices
# define K_W 0
# define K_A 1
# define K_S 2
# define K_D 3
# define K_LEFT 4
# define K_RIGHT 5

// Texture indices
# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3

#endif