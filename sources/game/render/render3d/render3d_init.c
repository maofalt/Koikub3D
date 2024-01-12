#include "structures.h"
#include "draw_utils.h"

#include "render_3D.h"
// #include "maths_utils.h"
// #include "ressources_managers.h"

int	render_3d_init(t_3d_render *render,
	t_canvas *canvas,
	t_camera *camera,
	t_map_data *map)
{
	render->canvas = canvas;
	render->camera = camera;
	render->map = map;
	render->middle.x = canvas->size.x / 2;
	render->middle.y = canvas->size.y / 2;
	render->middle.w = 0;
	render->middle.z = 0;
	render->top_array = ft_calloc(canvas->size.x, sizeof(double));
	render->bottom_array = ft_calloc(canvas->size.x, sizeof(double));
	render->z_buffer = ft_calloc(canvas->size.x * canvas->size.y,
		sizeof(render->z_buffer));
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
