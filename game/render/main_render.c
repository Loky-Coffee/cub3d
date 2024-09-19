#include "../../include/cub3d.h"

//					---BLUEPRINT---					//
	// create mlx window instance
	// create plazer vector and pixel and draw it
	// create map array by hand
	// print pixels 64 x 64 onto the window
	// start the raycasting


//					---TODO:---					//
	//TODO: add connection to main struct


static char **create_map(void) //TODO: only for testing
 {
    int rows = 6;
    char **map;

    // Speicherplatz für Zeilen reservieren
    map = (char **)malloc(rows * sizeof(char *));
    if (!map)
        return NULL;

    // Zeilen manuell befüllen
    map[0] = strdup("111111111111");
    map[1] = strdup("100000000001");
    map[2] = strdup("111110000001");
    map[3] = strdup("100000011111");
    map[4] = strdup("100000000001");
    map[5] = strdup("111111111111");

    return map;
}

void render_game(void)
{
	t_color clr;
	int i = 7;
	
	clr.color = 0xFF0000FF;

	ren_draw_table(game()->img, game()->map, 6, 12); // FILL IN ACTUAL HEIGHT AND WIDTH
	while(i != 0)
		ren_draw_circle(game()->img, game()->player.pos.x, game()->player.pos.y, i--, clr);

	cast_ray_n_draw(game()->img, game()->player.angle, clr, true);
}

void render_movement(void)
{
	if (game()->player.move_up)
        game()->player.pos.y -= 1.00;
    if (game()->player.move_down)
        game()->player.pos.y += 1.00;
    if (game()->player.move_left)
        game()->player.pos.x -= 1.00;
    if (game()->player.move_right)
        game()->player.pos.x += 1.00;
	if (game()->player.look_right)
        game()->player.angle += 0.10;
	else if (game()->player.look_left)
        game()->player.angle -= 0.10;
	if (game()->player.angle < 0)
		game()->player.angle += 2 * PI;
	if (game()->player.angle > 2 * PI)
		game()->player.angle -= 2 * PI;
	printf("%f\n", game()->player.angle);
}

// void cast_ray()

void render_loop(void *param)
{
	(void)param;

	render_movement();
	render_game();
}

int	main_render(void)
{
	t_color clr;
	clr.color = 0xFF0000FF;

	if (initialise_game())
		return (1); //TODO: error handling
	game()->map = create_map();
	
	//========--TESTING--========//
	main_hooks();
	//===========================//

	mlx_loop(game()->mlx);
	mlx_terminate(game()->mlx);
	// exit funciton
	return (0);
}
