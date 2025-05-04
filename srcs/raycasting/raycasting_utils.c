#include "cube.h"

int	two_point_distance(double x, double y, double x2, double y2)
{
	double	distance;

	distance = sqrt(pow((x2 - x), 2) + pow((y2 - y), 2));
	return (distance);
}