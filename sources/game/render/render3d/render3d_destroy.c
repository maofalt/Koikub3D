#include "structures.h"
#include "structures_utils.h"

void	render_3d_destroy(t_3d_render *render)
{
	free(render->top_array);
	free(render->bottom_array);
	free(render->z_buffer);
	circular_queue_destroy(render->queue);
	render->bottom_array = NULL;
	render->top_array = NULL;
	render->queue = NULL;
}
