/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteudin <csteudin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 06:31:41 by csteudin          #+#    #+#             */
/*   Updated: 2024/10/10 11:01:29 by csteudin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_BONUS_H
# define RENDER_BONUS_H

//---------------- defines ----------------//

# define STD_WIDTH 1920
# define STD_HEIGHT 1080
# define TILE 64
# define PI 3.1415926535
# define RA 6.283185307
# define SPEED 7.00
# define FOV 1.0472
# define SENSITIVITY 0.002
# define MAP_SCALE 0.3
//---------------- structs ----------------//

typedef enum move
{
	MOV_UP,
	MOV_DOWN,
	MOV_LEFT,
	MOV_RIGHT
}					t_move;

typedef struct s_vec_2
{
	float			x;
	float			y;
}					t_vec_2;

typedef struct s_vec_2_int
{
	u_int32_t		x;
	u_int32_t		y;
}					t_vec_2_int;

typedef struct s_player
{
	t_vec_2			pos;
	char			direction;
	float			angle;
	bool			move_up;
	bool			move_down;
	bool			move_left;
	bool			move_right;
	bool			look_right;
	bool			look_left;
	float			ray_x;
	float			ray_y;
}					t_player;

typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_image_t		*north_img;
	mlx_image_t		*south_img;
	mlx_image_t		*west_img;
	mlx_image_t		*east_img;
}					t_texture;

typedef struct s_ray
{
	float			ray_dir_x;
	float			ray_dir_y;
	float			ray_x;
	float			ray_y;
	float			wall_dist;
	int				is_horizontal;
	int				map_x;
	int				map_y;

}					t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		player;
	t_map			*map;
	t_texture		*tex;
	t_ray			ray;
	t_vec_2			mouse_delta;
}					t_game;

//---------------- functions ----------------//

//---MAIN---//
int					main(int argc, char **argv);
int					ft_exit(int exit_status);

//---MAIN-HOOKS---//
void				hook_keys(mlx_key_data_t keydata, void *param);
void				hook_resize(int32_t width, int32_t height, void *param);
void				hook_mouse_cursor(double xpos, double ypos, void *param);
void				main_hooks(void);

//---MAIN-RENDER---//
void				render_minimap(void);
int					main_render(t_map *map);
void				render_loop(void *param);

//---CALC---//
float				normalize_angle(float angle);
float				get_start_angle(char direction);
bool				hit_is_vertical(float angle);
float				get_hit_point(float ray_angle);

//---INIT---//
void				initialise_map(t_map *map);
int					initialise_mlx(void);
void				initialise_map_size(void);
int					initialise_game(t_map *map);

//---LOAD IMG---//
int					load_img(t_game *g);
int					delete_textures(void);
int					load_textures(void);

//---MOVE---//
int					wall_colission(float x, float y);
t_vec_2				get_next_pos(t_vec_2 pos, t_move mode);
void				move(t_vec_2 new_pos);
void				look(t_game *g);
void				render_movement(void);

//---RAYS---//
float				cast_ray_n_draw(mlx_image_t *img, float ray_angle, int clr,
						bool draw);
void				calculate_step_and_side_dist(t_ray *ray, t_vec_2 *step,
						t_vec_2 *side_dist, t_vec_2 d_dist);
void				perform_dda(t_vec_2 *side_dist, t_vec_2 *d_dist,
						t_vec_2 *step, t_ray *ray);
void				calculate_wall_dist_and_hit(t_vec_2 player_pos, t_ray *ray,
						t_vec_2 step);
void				raycast(float ray_angle, t_vec_2 player_pos, t_game *game,
						t_ray *ray);

//----UTILS----//
t_game				*game(void);
void				clear_image(mlx_image_t *img);
void				ren_draw_square(mlx_image_t *img, int x, int y, int clr);
void				ren_draw_table(mlx_image_t *img, char **map);
void				ren_draw_circle(int x_core, int y_core, int radius,
						int clr);

//---VIEW---//
mlx_image_t			*find_wall(void);
void				render_wall(double distance, int x_pos, double ray_angle,
						t_game *game);
void				render_view(t_game *game);

#endif