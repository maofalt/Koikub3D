#include "structures.h"
#include "draw_utils.h"

#include "render_3D.h"


void	render_portal(
	t_3d_render *render,
	t_segment_d	*wall,
	double left,
	double right
	)
{
	t_segment_d		projected_top;
	t_segment_d		projected_bot;
	double			coef_top;
	double			coef_bot;

	if (project_wall(render, wall, &projected_top, &projected_bot))
		return ;
	left = fmax(projected_top.point_a.x, left);
	right = fmin(projected_top.point_b.x, right);
	t_render_item_queue		new_item_queue;
	if (left < right)
	{
		new_item_queue.left = left;
		new_item_queue.right = right;
		new_item_queue.portal = wall->data.data.portal.destination;
		circular_queue_add(render->queue, &new_item_queue);
	}
	coef_bot = calc_segment_coef(&projected_bot);
	coef_top = calc_segment_coef(&projected_top);
	projected_top.point_a.y += coef_top * (left - projected_top.point_a.x);
	projected_top.point_b.y += coef_top * (right - projected_top.point_b.x);
	projected_bot.point_a.y += coef_bot * (left - projected_bot.point_a.x);
	projected_bot.point_b.y += coef_bot * (right - projected_bot.point_b.x);
	double bot_y = projected_bot.point_a.y;
	double top_y = projected_top.point_a.y;
	int x = left;
	while (x < right)
	{
		update_portal_ceil_floor_buffer(render, x, top_y, bot_y);
		top_y += coef_top;
		bot_y += coef_bot;
		++x;
	}
	projected_top.data = wall->data;
	projected_bot.data = wall->data;
	// draw_portal_ceil_offset(render, &projected_top, left, right);
	// draw_portal_floor_offset(render, &projected_bot, left, right);
	draw_portal_offset(render, wall, left, right);


}



void	render_sector(
	t_3d_render *render,
	t_render_item_queue *item_queue,
	t_tree_node *node
	)
{
	t_list					*seg_lst;
	t_segment_d				*segment;

	seg_lst = ((t_bsp_tree_node_data *)node->data)->sector_segments;
	while (seg_lst)
	{
		segment = seg_lst->content;
		if (segment->data.type == PORTAL)
		{
			if (segment != item_queue->portal)
				render_portal(render, segment,
					item_queue->left, item_queue->right);
		}
		else
		{
			draw_wall_texture(render, (t_segment_d *)seg_lst->content,
				item_queue->left, item_queue->right);
			// draw_solid_wall(render, (t_segment_d *)seg_lst->content,
			// 	item_queue->left, item_queue->right);
		}
		seg_lst = seg_lst->next;
	}
}


void	render_3d_draw(t_3d_render *render)
{
	t_tree_node				*node;
	t_render_item_queue		item_queue;

	ft_memset(render->z_buffer, 0,
		render->canvas->size.x * render->canvas->size.y * sizeof(double));
	for (int i = 0; i < render->canvas->size.x; i++)
	{
		render->top_array[i] = 0;//render->canvas->size.y;
		render->bottom_array[i] = render->canvas->size.y;
	} //TODO, maybe use a flag system instead


	node = bsp_search_point(render->map->bsp,
			vector4d_to_point2d(&render->camera->pos));
	item_queue.left = 0;
	item_queue.portal = NULL;
	item_queue.right = render->canvas->size.x;
	while (node)
	{
		render_sector(render, &item_queue, node);
		if (circular_queue_pop(render->queue, &item_queue) == 0)
			node = item_queue.portal->data.data.portal.tree_node_ptr;
		else
			node = NULL;
	}
}
