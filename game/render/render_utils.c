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
	u_int32_t width = game()->img->width;
	u_int32_t height = game()->img->height;

	clr.red = 0;
	clr.green = 0;
	clr.blue = 0;
	clr.alpha = 255;

	y = -1;
	while(++y < (int)height)
	{
		x = -1;
		while(++x < (int)width)
		{
			mlx_put_pixel(img, x, y, clr.color);
		}
	}
}

void ren_draw_square(mlx_image_t *img, int x, int y, int clr)
{
	int i;
	int j;

	i = 0;
	while(i < TILE - 1)
	{
		j = 0;
		while(j < TILE - 1)
		{
			mlx_put_pixel(img, x + i, y + j, clr);
			j++;
		}
		i++;
	}
}

void ren_draw_table(mlx_image_t *img, char **map, int row, int col) // MUSS NOCH ANGEPASST WERDEN
{
	int i;
	int j;

	(void)row;
	(void)col;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map && map[i][j] == '1')
				ren_draw_square(img, j * TILE, i * TILE, 0x00000000);
			else if (map && map[i][j] == '0')
				ren_draw_square(img, j * TILE, i * TILE, 0x0000FFFF);
			else if (map && (map[i][j] == 'N' || map[i][j] == 'S'))
				ren_draw_square(img, j * TILE, i * TILE, 0x0000FFFF);
			else if (map && (map[i][j] == 'E' || map[i][j] == 'W'))
				ren_draw_square(img, j * TILE, i * TILE, 0x0000FFFF);
			j++;
		}
		i++;
	}
}

void ren_draw_circle(mlx_image_t *img, int x_core, int y_core, int radius, int clr)
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
		mlx_put_pixel(img, x_core - x, y_core + y, clr);
    	mlx_put_pixel(img, x_core - y, y_core - x, clr);
        mlx_put_pixel(img, x_core + x, y_core - y, clr);
        mlx_put_pixel(img, x_core + y, y_core + x, clr);
		rad = err;
		if (rad <= y)
			err += ++y * 2 + 1;
		if (rad > x || err > y)
		{
			err += ++x * 2 + 1;
		}
	}
}
