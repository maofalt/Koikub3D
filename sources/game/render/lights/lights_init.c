#include "draw_utils.h"
#include "structures.h"
#include "render_3D.h"

// typedef struct t_point_light
// {
// 	t_vector4d pos;
// 	t_color color;
// } t_point_light;

// typedef struct s_directional_light
// {
// 	t_vector4d pos;
// 	t_color color;
// 	t_vector4d dir;
// } t_directional_light;

// t_directional_light directional_lights[] = {

// 	{.pos = {.vec = {2, 2, 0, 0}}, .color = {.r = 1, .g = 0, .b = 2}, .dir = {.vec = {0, 0, 0, 0}}},

// };

// t_point_light point_lights[] = {
// 	// { .pos = { .vec = { 2, 2, -1, 0 } }, .color = { .r = 1, .g = 0, .b = 0.5 } },
// 	{.pos = {.vec = {7, 9.9, 2, 0}}, .color = {.r = 1, .g = 0, .b = 2}},
// 	{.pos = {.vec = {20, 20, 0, 0}}, .color = {.r = 5, .g = 1, .b = 0}},
// 	{.pos = {.vec = {83.573784, 13.590420, 0, 0}}, .color = {.r = 5, .g = 1, .b = 0}},
// 	// {.pos = {.vec = {2, 2, 2.547757494560237, 0}}, .color = {.r = 0, .g = 1, .b = 0}},
// 	{.pos = {.vec = {15, 8, -3.088479523707859, 0}}, .color = {.r = 0, .g = 0, .b = 1}},
// 	{ .pos = { .vec = { 8.597030255509164, 35, 2.8024089098964993, 0 } }, .color = { .r = 1, .g = 0, .b = 0 } },
// };

// typedef enum e_light_type
// {
// 	POINT_LIGHT,
// 	DIRECTIONAL_LIGHT
// }	t_light_type;

// typedef struct s_light
// {
// 	t_light_type	type;
// 	t_vector4d		pos;
// 	t_vector4d		dir;
// 	t_color			color;
// 	double			intensity;
// 	bool			show_lens_flare;
// }	t_light;

t_light lights[] =
{
	{.type = DIRECTIONAL_LIGHT, .pos = {.vec = {2, 2, 1, 0}}, .color = {.r = 1, .g = 0, .b = 2}, .dir = {.vec = {0, 0, 0, 0}}, .intensity = 1, .show_lens_flare = true},
	{.type = POINT_LIGHT, .pos = {.vec = {7, 9.9, 1, 0}}, .color = {.r = 5, .g = 1, .b = 0}, .dir = {.vec = {0, 0, 0, 0}}, .intensity = 1, .show_lens_flare = true},
	{.type = POINT_LIGHT, .pos = {.vec = {20, 20, 1, 0}}, .color = {.r = 5, .g = 1, .b = 0}, .dir = {.vec = {0, 0, 0, 0}}, .intensity = 1, .show_lens_flare = true},
	{.type = POINT_LIGHT, .pos = {.vec = {83.573784, 13.590420, 1, 0}}, .color = {.r = 5, .g = 1, .b = 0}, .dir = {.vec = {0, 0, 0, 0}}, .intensity = 1, .show_lens_flare = true},
	{.type = POINT_LIGHT, .pos = {.vec = {15, 8, -4.088479523707859, 0}}, .color = {.r = 0, .g = 0, .b = 1}, .dir = {.vec = {0, 0, 0, 0}}, .intensity = 1, .show_lens_flare = true},
	{.type = POINT_LIGHT, .pos = {.vec = {8.597030255509164, 35, 3.8024089098964993, 0}}, .color = {.r = 1, .g = 0, .b = 0}, .dir = {.vec = {0, 0, 0, 0}}, .intensity = 1, .show_lens_flare = true},
};


void	render_init_lights(t_3d_render *render)
{
	const int light_count = sizeof(lights) / sizeof(lights[0]);
	int	i;

	i = 0;
	while (i < light_count)
	{
		render->lights_data.lights[i] = lights[i];
		++i;
	}
	render->lights_data.light_count = light_count;
}
