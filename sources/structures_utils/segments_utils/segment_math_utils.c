#include <assert.h>
#include "structures.h"

double	calc_segment_coef(
			t_segment_d *segment
			)
{
	t_point2d	delta;

	delta.x = segment->point_b.x - segment->point_a.x;
	delta.y = segment->point_b.y - segment->point_a.y;
	assert(delta.x != 0);
	return (delta.y / fabs(delta.x));
}
