#ifndef RENDER_H
# define RENDER_H

//---------------- defines ----------------//

# define STD_WIDTH	1024
# define STD_HEIGHT 512
# define FOV		90
# define TILE		64
# define PI			3.1415926535

//---------------- structs ----------------//

typedef struct s_vec_2
{
	double x;
	double y;
}				t_vec_2;

typedef struct s_player
{
	t_vec_2 pos;
	double angle;
	bool move_up;
	bool move_down;
	bool move_left;
	bool move_right;
	bool look_right;
	bool look_left;
	// add more here

}				t_player;
typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
	t_map		*map;
	// add more here
	
}				t_game;

//---------------- functions ----------------//

//---MAIN
int main_render(t_map *map);
void render_game(void);
void render_movement(void);
void render_loop(void *param);

//---INIT
int		initialise_mlx(void);
void	initialise_map_size(void);
int		initialise_game(t_map *map);

//----UTILS----//
t_game *game(void);
void clear_image(mlx_image_t *img);
void ren_draw_square(mlx_image_t *img, int x, int y, t_color clr);
void ren_draw_table(mlx_image_t *img, char **map, int row, int col);
void ren_draw_circle(mlx_image_t *img, int x_core, int y_core, int radius, t_color clr);

//---HOOKS
void hook_move(mlx_key_data_t keydata, void *param);
void main_hooks();

//---RAYS
int wall_colission(double x, double y);
void cast_ray_n_draw(mlx_image_t *img, double ray_angle, t_color clr, bool draw);


#endif