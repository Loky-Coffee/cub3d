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
	while(i < (TILE * MAP_SCALE) - 2)
	{
		j = 0;
		while(j < (TILE * MAP_SCALE) - 2)
		{
			mlx_put_pixel(img, x + i, y + j, clr);
			j++;
		}
		i++;
	}
}

void ren_draw_table(mlx_image_t *img, char **map)
{
	int i;
	int j;
	int off_x;
	int off_y;


	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			off_x = 10 + ((j * TILE) * MAP_SCALE);
			off_y = 10 + ((i * TILE) * MAP_SCALE);
			if (map && map[i][j] == '1')
				ren_draw_square(img, off_x, off_y, 0x00000000);
			else if (map && map[i][j] == '0')
				ren_draw_square(img, off_x, off_y, 0x000000FF);
			else if (map && (map[i][j] == 'N' || map[i][j] == 'S'))
				ren_draw_square(img, off_x, off_y, 0x000000FF);
			else if (map && (map[i][j] == 'E' || map[i][j] == 'W'))
				ren_draw_square(img, off_x, off_y, 0x000000FF);
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
