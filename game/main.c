// PLEASE KEINE HEADER HIER IST DIE HAUPT MAIN UND KANN SEIN DAS WIR BEIDE HIER WAS SCHREIBEN MUSSEN!!!!

#include "../include/cub3d.h"

int main(int argc, char **argv)
{
	t_p parsing;
	t_map map;

	initialise_map(&map);
	if (main_parsing(argc, argv, &map, &parsing) != 0)
		return (EXIT_FAILURE);
	if (main_render(&map) != 0)
	    return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

//--------TODO:--------//
// -- add feature NSWE start angle
// -- change for resizing features
// --