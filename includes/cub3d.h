#ifndef CUB3D_H
# define CUB3D_H

// System headers
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <errno.h>

// MLX header (adjust path as needed)
# include "../minilibx-linux/mlx.h"

// Libft header
# include "../libft/libft.h"

// Project headers
# include "structs.h"

// Parsing functions
int			parse_cub_file(char *filename, t_game *game);
int			parse_textures(char *line, t_game *game);
int			parse_colors(char *line, t_game *game);
int			parse_map(int fd, t_game *game);
int			validate_map(t_game *game);
int			check_map_borders(t_game *game);
int			validate_player_position(t_game *game);
int			validate_texture_file(char *path);
int			check_closed(char **tmp, t_game *g);
int			mem_error(void);
char		**create_map_copy(t_game *game);
void		flood_fill(t_game *game, char **temp_map, int x, int y);
int			scan_for_player(t_game *game);
void		trim_line_end(char *trimmed);
int			get_texture_index(char *trimmed);
void		trim_color_line(char *trimmed);
t_color		*get_target_color(char *trimmed, t_game *game);
int			parse_rgb(char *str, t_color *color);
int			get_line_length(char *line);
int			process_line(char *line, t_game *game);
int			check_elements(t_game *game);
int			add_mapline(t_mapline **head, t_mapline **tail, char *line);
void		free_maplines(t_mapline *head);
int			allocate_and_fill_grid(t_grid_context *ctx);
int			read_file_loop(int fd, t_parse_ctx *ctx);
int			finalize_map_parse(t_parse_ctx *ctx);
t_map_dims	calculate_map_dimensions(t_mapline *lines);

// MLX and graphics functions
int			init_mlx(t_game *game);
int			load_textures(t_game *game);
void		my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int			get_texture_color(t_texture *texture, int x, int y);
void		draw_vertical_line(t_game *game, int x, t_ray *ray, int tex_num);

// Raycasting functions
void		raycaster(t_game *game);
void		init_ray(t_ray *ray, t_game *game, int x);
void		calculate_step_and_side_dist(t_ray *ray, t_game *game);
void		perform_dda(t_ray *ray, t_game *game);
void		calculate_wall_height(t_ray *ray, t_game *game);
void		calculate_texture_coordinates(t_ray *ray, t_game *game,
				int *tex_num);

// Event handling functions
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
int			handle_movement(t_game *game);
int			close_window(t_game *game);
void		move_forward(t_game *game);
void		move_backward(t_game *game);
void		move_left(t_game *game);
void		move_right(t_game *game);
void		rotate_left(t_game *game);
void		rotate_right(t_game *game);

// Utility functions
void		exit_error(char *message, t_game *game);
void		free_map(char **map);
void		cleanup_game(t_game *game);
int			is_valid_map_char(char c);
void		trim_trailing_whitespace(char *line);
int			create_line_node(char *line, t_line_data *data);
void		init_player_direction(t_game *game);
int			create_rgb(t_color color);
char		*skip_spaces(char *str);
int			count_split_elements(char **split);
void		free_split(char **split);

// Minimap functions
void		draw_minimap_rect(t_game *game, t_rect_data *rect);
void		draw_minimap_player(t_game *game, int center_x, int center_y);
void		draw_minimap_border(t_game *game);
void		draw_minimap(t_game *game);

// Mouse functions
int			mouse_move(int x, int y, t_game *game);
void		hide_mouse_cursor(t_game *game);
void		show_mouse_cursor(t_game *game);

char		*get_next_line(int fd);

void		free_line_list(t_line_node *head);

// Minimap configuration
# define MINIMAP_SIZE 200
# define MINIMAP_SCALE 8
# define MINIMAP_OFFSET 20
# define MINIMAP_BORDER 2

// Colors for minimap
# define COLOR_WALL 0x808080
# define COLOR_FLOOR 0x202020
# define COLOR_PLAYER 0x00FF00
# define COLOR_BORDER 0xFFFFFF
# define COLOR_VIEW_CONE 0x00FF00

# define MOUSE_SENSITIVITY 0.002
#endif