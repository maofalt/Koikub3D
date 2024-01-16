#include "draw_utils.h"
#include "structures.h"
#include "maths_utils.h"
#include "render_3D.h"


double q_rsqrt(double number)
{
	// long i;
	// float x2, y;
	// const float threehalfs = 1.5F;

	// x2 = number * 0.5F;
	// y  = number;
	// i  = * ( long * ) &y;                       // evil floating point bit level hacking
	// i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	// y  = * ( double * ) &i;
	// y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
	// // y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return 1 / sqrt(number);
}
void normalize_vector_2d(t_vector4d *vec)
{
	double reverse_lenght = q_rsqrt(vec->x * vec->x + vec->y * vec->y);
	vec->vec[0] *= reverse_lenght;
	vec->vec[1] *= reverse_lenght;
}

void normalize_vector_3d(t_vector4d *vec)
{
	double reverse_lenght = q_rsqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	vec->vec[0] *= reverse_lenght;
	vec->vec[1] *= reverse_lenght;
	vec->vec[2] *= reverse_lenght;
}

double dot_product_2d(t_vector4d *vec1, t_vector4d *vec2)
{
	// double result = vec1->x * vec2->x + vec1->y * vec2->y;
	double result = vec1->x * vec2->x + vec1->y * vec2->y;
	return result;
}
double dot_product_3d(t_vector4d *vec1, t_vector4d *vec2)
{
	// double result = vec1->x * vec2->x + vec1->y * vec2->y;
	double result = vec1->x * vec2->x + vec1->y * vec2->y + +vec1->z * vec2->z;
	return result;
}

// double point_cross_product()
// {
// 	t_vector4d	ab;
// 	t_vector4d	ap;
// 	double		cross_product;

// 	ab.vec = separator->point_b.vec - separator->point_a.vec;
// 	ap.vec = segment_point->vec - separator->point_a.vec;
// 	cross_product = ab.x * ap.y - ab.y * ap.x;
// }




	t_vector4d lights[40] = {
		(t_vector4d){.vec = {2, 2, 0, 0}},
		(t_vector4d){.vec = {10, 2, 0, 0}},
		(t_vector4d){.vec = {40, 2, 0, 0}},
		(t_vector4d){.vec = {2, 10, 0, 0}},
		(t_vector4d){.vec = {10, 10, 0, 0}},
		(t_vector4d){.vec = {40, 10, 0, 0}},
		(t_vector4d){.vec = {2, 40, 0, 0}},
		(t_vector4d){.vec = {10, 40, 0, 0}},
		(t_vector4d){.vec = {40, 40, 0, 0}},
		(t_vector4d){.vec = {2, 2, 10, 0}},
		(t_vector4d){.vec = {20, 20, 20, 0}},
		(t_vector4d){.vec = {30, 30, 30, 0}},
		(t_vector4d){.vec = {50, 50, 50, 0}},
		(t_vector4d){.vec = {5, 5, 5, 0}},
		(t_vector4d){.vec = {15, 15, 15, 0}},
		(t_vector4d){.vec = {3, 3, 3, 0}},
		(t_vector4d){.vec = {6, 6, 6, 0}},
		(t_vector4d){.vec = {9, 9, 9, 0}},
		(t_vector4d){.vec = {12, 12, 12, 0}},
		(t_vector4d){.vec = {15, 15, 15, 0}},
		(t_vector4d){.vec = {18, 18, 18, 0}},
		(t_vector4d){.vec = {21, 21, 21, 0}},
		(t_vector4d){.vec = {24, 24, 24, 0}},
		(t_vector4d){.vec = {27, 27, 27, 0}},
		(t_vector4d){.vec = {30, 30, 30, 0}},
		(t_vector4d){.vec = {33, 33, 33, 0}},
		(t_vector4d){.vec = {36, 36, 36, 0}},
		(t_vector4d){.vec = {39, 39, 39, 0}},
		(t_vector4d){.vec = {42, 42, 42, 0}},
		(t_vector4d){.vec = {45, 45, 45, 0}},
		(t_vector4d){.vec = {48, 48, 48, 0}},
		(t_vector4d){.vec = {51, 51, 51, 0}},
		(t_vector4d){.vec = {54, 54, 54, 0}},
		(t_vector4d){.vec = {57, 57, 57, 0}},
		(t_vector4d){.vec = {60, 60, 60, 0}},
	};

t_color shader_deferred_shading(t_color original_color, int offset, t_3d_render *render, double time_mouvement)
{
	t_color lighting = original_color;
	double luminosity = 0.05;
	lighting.r *= luminosity * 0.5;
	lighting.g *= luminosity;
	lighting.b *= luminosity * 3;

	t_vector4d normal = render->buffers.normal[offset];
	t_vector4d world_pos = render->buffers.world_pos[offset];
	// t_color color = render->buffers.color[offset];
	// double depth = render->buffers.depth[offset];

	for (int i = 0; i < 3; i++)
	{
		t_vector4d light_pos = lights[i];
		light_pos.z = sin(time_mouvement * 8) * 0.5;
		light_pos.x += cos(time_mouvement * 8) * 0.5;
		// light_pos = transform_camera_relative_point(light_pos, render->camera);

		t_vector4d light_dir = {.vec = {0, 0, 0, 0}};
		light_dir.vec = light_pos.vec - world_pos.vec;
		normalize_vector_3d(&light_dir);

		double diffuse = fmax(dot_product_3d(&normal, &light_dir), 0.0);
		double dist = sqrt((light_pos.x - world_pos.x) * (light_pos.x - world_pos.x) + (light_pos.y - world_pos.y) * (light_pos.y - world_pos.y) + (light_pos.z - world_pos.z) * (light_pos.z - world_pos.z));
		double attenuation = 1.0 / (dist);

		lighting.r += original_color.r * fmin(1, diffuse * attenuation * fmax(0, (sin(time_mouvement * 4) - 0.5) * 2));
		lighting.g += original_color.g * fmin(1, diffuse * attenuation * 2);
		// lighting.b += original_color.b * fmin(1, diffuse * attenuation);
	}
	// lighting.rgb_color += shader_torch(original_color, offset, render->canvas->size.x, render->canvas->size.y, render).rgb_color;

	// {


	// 	t_vector4d light_pos = (t_vector4d){.vec = {0, 1, 0, 0}};
	// 	// light_pos = reverse_transform_camera_relative_point(light_pos, render->camera);

	// 	t_vector4d light_dir = {.vec = {0, 0, 0, 0}};
	// 	light_dir.vec = light_pos.vec - world_pos.vec;
	// 	normalize_vector_3d(&light_dir);

	// 	double diffuse = fmax(dot_product_3d(&normal, &light_dir), 0.0);
	// 	double dist = sqrt((light_pos.x - world_pos.x) * (light_pos.x - world_pos.x) + (light_pos.y - world_pos.y) * (light_pos.y - world_pos.y) + (light_pos.z - world_pos.z) * (light_pos.z - world_pos.z));
	// 	double attenuation = 0.5 / (dist * dist);

	// 	lighting.r += original_color.r * fmin(1, diffuse * attenuation);
	// 	// lighting.g += original_color.g * fmin(1, diffuse * attenuation * fmax(0, sin(time_mouvement * 4) - 0.5));
	// 	// lighting.b += original_color.b * fmin(1, diffuse * attenuation);

	// }

	return lighting;
}
