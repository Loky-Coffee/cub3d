#include "../../include/cub3d.h"


double normalize_angle(double angle)
{
	while (angle < 0)
		angle += RA;
	while (angle >= RA)
		angle -= RA;
	return angle;
}