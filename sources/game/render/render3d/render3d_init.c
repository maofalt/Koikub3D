#include "structures.h"
#include "draw_utils.h"

#include "render_3D.h"
// #include "maths_utils.h"
// #include "ressources_managers.h"

static int	init_buffers(t_3d_render *render, int width, int height)
{
	render->z_buffer = ft_calloc(width * height,
		sizeof(render->z_buffer[0]));
	render->buffers.color = ft_calloc(width * height,
		sizeof(render->buffers.color[0]));

	if ((render->z_buffer && render->buffers.color) == 0)
	{
		free(render->z_buffer);
		free(render->buffers.color);
		render->buffers.color = NULL;
		render->z_buffer = NULL;
		return (1);
	}

	return (0);
}

int	render_3d_init(t_3d_render *render,
	t_canvas *canvas,
	t_camera *camera,
	t_map_data *map)
{
	render->canvas = canvas;
	render->camera = camera;
	render->scale_factor_x = 8;
	render->scale_factor_y = 8;
	render->width = canvas->size.x / render->scale_factor_x;
	render->height = canvas->size.y / render->scale_factor_y;
	render->map = map;
	render->middle.x = render->width / 2;
	render->middle.y = render->height / 2;
	render->middle.w = 0;
	render->middle.z = 0;
	render->top_array = ft_calloc(render->width, sizeof(double));
	render->bottom_array = ft_calloc(render->width, sizeof(double));
	init_buffers(render, render->width, render->height);
	render->queue = circular_queue_create(RENDER_QUEUE_SIZE,
			sizeof(t_render_item_queue));
	if (render->top_array == NULL
		|| render->bottom_array == NULL
		|| render->z_buffer == NULL
		|| render->queue == NULL)
	{
		render_3d_destroy(render);
		return (1);
	}
	return (0);
}
