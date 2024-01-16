
#include "draw_utils.h"
#include "structures.h"
#include "render_3D.h"

void	game_post_process_frame(t_3d_render *render)
{
	const int max_offset = render->width * render->height;
	int	i;
	static double frame = 0;

	frame += 0.1;
	i = 0;
	while (i < max_offset)
	{
		// if (render->buffers.depth[i] >= 1)
		// {
		// 	render->canvas->pixels[i].a /= render->buffers.depth[i];
		// 	render->canvas->pixels[i].r /= render->buffers.depth[i];
		// 	render->canvas->pixels[i].g /= render->buffers.depth[i];
		// 	render->canvas->pixels[i].b /= render->buffers.depth[i];
		// }
		// render->buffers.color[i] = shader_torch(render->buffers.color[i], i,
		// 	render->width, render->height, render);
		render->buffers.color[i] = shader_deferred_shading(render->buffers.color[i], i,
			 render, frame);
		++i;
	}
}
