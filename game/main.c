#include <stdio.h>
#include "../include/cub3d.h"

int main (int argc, char **argv)
{
	int ret_val;

	ret_val = main_parsing(argc, argv);
	if (ret_val <= 0)
		ret_val += main_render();
	return (ret_val);
}