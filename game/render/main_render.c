#include "../../include/cub3d.h"

//					---BLUEPRINT---					//
	// create mlx window instance
	// create plazer vector and pixel and draw it
	// create map array by hand
	// print pixels 64 x 64 onto the window
	// start the raycasting


//					---TODO:---					//
	//TODO: add connection to main struct

char map[6][13] = 
{
    "111111111111",  
    "100000000001",  
    "111110000001", 
    "100000011111",  
    "100000000001",  
    "111111111111"   
};

void render_game(void)
{
	t_color clr;
	
	clr.color = 0xFF0000FF;

	ren_draw_table(game()->img, map, 6, 12); // FILL IN ACTUAL HEIGHT AND WIDTH
	ren_draw_circle(game()->img, game()->player.pos.x, game()->player.pos.y, 8, clr);

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

}

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

	
	//========--TESTING--========//
	main_hooks();
	//===========================//


	mlx_loop(game()->mlx);
	mlx_terminate(game()->mlx);
	// exit funciton
	return (0);
}
