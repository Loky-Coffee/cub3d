#include "../../include/cub3d.h"

/*
*	> cosinus is for calculating how much movement is on the X
*	> sinus is for how much on the y
*	> then just multiply it with the speed and the you got your new position
*/
void render_movement(void)
{
	if (game()->player.move_up)
	{
		game()->player.pos.x += cos(game()->player.angle) * SPEED;
		game()->player.pos.y += sin(game()->player.angle) * SPEED;
	}
	if (game()->player.move_down)
	{
		game()->player.pos.x -= cos(game()->player.angle) * SPEED;
		game()->player.pos.y -= sin(game()->player.angle) * SPEED;
	}
	if (game()->player.move_left)
	{
		game()->player.pos.x -= cos(game()->player.angle + PI / 2) * SPEED;
		game()->player.pos.y -= sin(game()->player.angle + PI / 2) * SPEED;
	}
	if (game()->player.move_right)
	{
		game()->player.pos.x += cos(game()->player.angle + PI / 2) * SPEED;
		game()->player.pos.y += sin(game()->player.angle + PI / 2) * SPEED;
	}
	if (game()->player.look_right)
		game()->player.angle += 0.20;
	else if (game()->player.look_left)
		game()->player.angle -= 0.20;
	game()->player.angle = normalize_angle(game()->player.angle);
}