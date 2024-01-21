
#include "draw_utils.h"
#include "structures.h"
#include "render_3D.h"


//TODO move this in .h
t_color_64 shader_camera_light_bloom(t_color_64 original_color, int offset, t_3d_render *render, double time_mouvement);
t_color shader_small_camera_tilt(t_color original_color, int offset, t_3d_render *render, double movement_offset);

void compute_lights_visibility(t_3d_render *render);

void	game_post_process_frame(t_3d_render *render)
{
	const int max_offset = render->width * render->height;
	int	i;
	static double frame = 0;
	t_color_64 color;

	frame += 0.1;
	i = 0;
	compute_lights_visibility(render);
	while (i < max_offset)
	{
		color.a = render->buffers.color[i].a;
		color.r = render->buffers.color[i].r;
		color.g = render->buffers.color[i].g;
		color.b = render->buffers.color[i].b;
		color = shader_deferred_shading(color, i,
			 render, frame);
		color = shader_camera_light_bloom(color, i,
			 render, frame);
		render->buffers.color_bis[i].a = fmin(color.a, 255);
		render->buffers.color_bis[i].r = fmin(color.r, 255);
		render->buffers.color_bis[i].g = fmin(color.g, 255);
		render->buffers.color_bis[i].b = fmin(color.b, 255);
		++i;
	}
	i = 0;
	while (i < max_offset)
	{
		render->buffers.color[i] = render->buffers.color_bis[i];
		render->buffers.color[i] = shader_small_camera_tilt(
				render->buffers.color[i], i, render, frame);
		++i;
	}
}
