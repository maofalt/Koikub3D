
#include "structures.h"

static double	dot_product_2d(t_vector4d *vec1, t_vector4d *vec2)
{
	double	result;

	result = vec1->x * vec2->x + vec1->y * vec2->y;
	return (result);
}

bool	segment_circle_intersection(t_segment_d *segment, t_circle *circle)
{
	t_vector4d	line_vec;
	t_vector4d	circle_vec;
	double		t;
	t_vector4d	closest_point;
	t_vector4d	dist_vec;

	line_vec.vec = segment->point_b.vec - segment->point_a.vec;
	circle_vec.vec = circle->center.vec - segment->point_a.vec;
	t = dot_product_2d(&circle_vec, &line_vec) / dot_product_2d(&line_vec,
			&line_vec);
	t = fmaxf(0, fminf(1, t));
	closest_point.vec = segment->point_a.vec + t * line_vec.vec;
	dist_vec.vec = circle->center.vec - closest_point.vec;
	return (dot_product_2d(&dist_vec, &dist_vec) <= circle->radius
		* circle->radius);
}
