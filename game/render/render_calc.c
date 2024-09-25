#include "../../include/cub3d.h"

float normalize_angle(float angle)
{
	while (angle < 0)
		angle += RA;
	while (angle >= RA)
		angle -= RA;
	return angle;
}