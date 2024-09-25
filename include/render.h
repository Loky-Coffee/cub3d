


#ifndef RENDER_H
# define RENDER_H

//---------------- defines ----------------//

# define STD_WIDTH	1920
# define STD_HEIGHT 1080
# define TILE		64
# define PI			3.1415926535
# define RA			2 * PI
# define SPEED		7.00
# define DEG_TO_RAD(deg) ((deg) * PI / 180.0)
# define FOV DEG_TO_RAD(80)

//---------------- structs ----------------//

typedef struct s_vec_2
{
	float x;
	float y;
}				t_vec_2;

typedef struct s_player
{
	t_vec_2 pos;
	float			angle;
	bool			move_up;
	bool			move_down;
	bool			move_left;
	bool			move_right;
	bool			look_right;
	bool			look_left;
	float			ray_x;
	float			ray_y;
}				t_player;

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
}				t_texture;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		player;
	t_map			*map;
	t_texture		*tex;
}				t_game;

//---------------- functions ----------------//

//---MAIN-HOOKS---//
void	hook_keys(mlx_key_data_t keydata, void *param);
// void hook_mouse_cursor(float xpos, float ypos, void * param)
void	main_hooks();

//---MAIN-RENDER---//
int		main_render(t_map *map);
void	render_loop(void *param);
//ADD TO BONUS....
void	render_minimap(void);

//---CALC---//
float	normalize_angle(float angle);

//---INIT---//
void	initialise_map(t_map *map);
int		initialise_mlx(void);
void	initialise_map_size(void);
int		load_textures(void);
int		initialise_game(t_map *map);

//---MOVE---//
void		render_movement(void);

//---RAYS---//
int			wall_colission(float x, float y);
float		cast_ray_n_draw(mlx_image_t *img, float ray_angle, int clr, bool draw);

//----UTILS----//
t_game		*game(void);
void		clear_image(mlx_image_t *img);
void		ren_draw_square(mlx_image_t *img, int x, int y, int clr);
void		ren_draw_table(mlx_image_t *img, char **map, int row, int col);
void		ren_draw_circle(mlx_image_t *img, int x_core, int y_core, int radius, int clr);

//---VIEW---//
mlx_image_t	*find_wall();
void		render_wall(double distance, int x_pos, double ray_angle, t_game *game);
void		render_view(t_game *game);

#endif