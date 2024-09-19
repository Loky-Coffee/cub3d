// PLEASE KEINE HEADER HIER IST DIE HAUPT MAIN UND KANN SEIN DAS WIR BEIDE HIER WAS SCHREIBEN MUSSEN!!!!

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	(void)argc; // for testing puropses only
	(void)argv;
	
	// if(!main_parsing(argc, argv))
	// 	return (EXIT_FAILURE);
	
	if (!main_render())
		return (EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}
