#include "../../include/cub3d.h"

t_game *game(void)
{
	static t_game game;

	return (&game);
}

void clear_image(mlx_image_t *img)
{
	int x;
	int y;
	t_color clr;

	clr.red = 0;
	clr.green = 0;
	clr.blue = 0;
	clr.alpha = 255;

	y = -1;
	while(++y < STD_HEIGHT)
	{
		x = -1;
		while(++x < STD_WIDTH)
		{
			mlx_put_pixel(img, x, y, clr.color);
			printf("pix = X = %d  ||  Y =  %d ", x, y);
		}
	}
}

void ren_draw_square(mlx_image_t *img, int x, int y, t_color clr)
{
	int i;
	int j;

	i = 0;
	while(i < TILE - 1) // MINUS ONE FOR THE GITTERS MA FRIEND
	{
		j = 0;
		while(j < TILE - 1)
		{
			mlx_put_pixel(img, x + i, y + j, clr.color);
			j++;
		}
		i++;
	}
}

void ren_draw_table(mlx_image_t *img, char map[6][13], int row, int col) // MUSS NOCH ANGEPASST WERDEN
{
	int i;
	int j;
	t_color wall;
	t_color floor;

	wall.color = 0x000000FF;
	floor.color = 0xFFFFFFFF;

	i = 0;	
	while(i < row)
	{
		j = 0;
		while(j < col)
		{
			if (map[i][j] == '1')
				ren_draw_square(img, j * TILE, i * TILE, wall);
			else if (map[i][j] != ' ')
				ren_draw_square(img, j * TILE, i * TILE, floor);
			j++;
		}
		i++;
	}
}

void ren_draw_circle(mlx_image_t *img, int x_core, int y_core, int radius, t_color clr)
{
	int x;
	int y;
	int rad;
	int err;

	x = -radius;
	y = 0;
	err = 2 - 2 * radius;
	while (x < 0)
	{
		mlx_put_pixel(img, x_core - x, y_core + y, clr.color);
    	mlx_put_pixel(img, x_core - y, y_core - x, clr.color);
        mlx_put_pixel(img, x_core + x, y_core - y, clr.color);
        mlx_put_pixel(img, x_core + y, y_core + x, clr.color);
		rad = err;
		if (rad <= y)
			err += ++y * 2 + 1;
		if (rad > x || err > y)
		{
			err += ++x * 2 + 1;
		}
	}
}
