#include "draw_utils.h"
#include "structures.h"
#include "maths_utils.h"
#include "render_3D.h"

t_color	shader_torch(t_color original_color, int offset, int width, int height, t_3d_render *render)
{
	int y = offset / width;
	int x = offset % width;
	double depth = render->z_buffer[offset];

	double center_dist = ((y - height/2) * (y - height/2)) + ((x - width/2) * (x - width/2));

	double opacity = 0.1/ fmax(depth * depth, 1);

	// depth = depth / (center_dist/1000);
	// if (center_dist < 10000)
	// {
		// depth -= 1 / sqrt(center_dist);
		// depth =  1;
	opacity +=  (0.5 / (depth*1.5)) * fmin(((50000 * fmin(1000, depth) / (center_dist*2))), 4);
	// }

	opacity = fmin(opacity, 1);
	opacity = fmax(opacity, 0);
	original_color.b *= opacity;
	original_color.g *= opacity;
	original_color.r *= opacity;
	original_color.a *= opacity;

	return (original_color);
}

