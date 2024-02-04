/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 05:07:33 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/04 05:28:49 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "render_3D.h"
#include "structures.h"
#include "structures_utils.h"

void	render_sector(t_3d_render *render,
		t_render_item_queue *item_queue,
		t_tree_node *node)
{
	t_list		*seg_lst;
	t_segment_d	*segment;

	seg_lst = ((t_bsp_tree_node_data *)node->data)->sector_segments;
	while (seg_lst)
	{
		segment = seg_lst->content;
		if (segment->data.type == PORTAL)
		{
			if (segment != item_queue->portal)
				render_portal(render, segment, item_queue->left,
					item_queue->right);
		}
		else
		{
			render_wall(render, segment, item_queue->left, item_queue->right);
		}
		seg_lst = seg_lst->next;
	}
}

void	draw_floor_ceil_color(t_3d_render *render)
{
	int		offset;
	int		mid_offset;
	double	dist_center;
	t_color	color;

	offset = render->height * render->width - 1;
	mid_offset = render->middle.y * render->width;
	while (offset > mid_offset)
	{
		dist_center = ((offset / render->width) - render->middle.y)
			/ render->middle.y;
		color = color_multiply_coeff(render->map->floor_color, dist_center);
		render->buffers.color[offset] = color;
		--offset;
	}
	while (offset >= 0)
	{
		dist_center = (render->middle.y - (offset / render->width))
			/ render->middle.y;
		color = color_multiply_coeff(render->map->ceil_color, dist_center);
		render->buffers.color[offset] = color;
		--offset;
	}
}

void	reset_frame(t_3d_render *render)
{
	int	i;

	ft_memset(render->buffers.depth, 0, render->width * render->height
		* sizeof(render->buffers.depth[0]));
	draw_floor_ceil_color(render);
	i = 0;
	while (i < render->width)
	{
		render->top_array[i] = 0;
		render->bottom_array[i] = render->height;
		++i;
	}
}

void	render_3d_draw(t_3d_render *render)
{
	t_tree_node			*node;
	t_render_item_queue	item_queue;

	reset_frame(render);
	node = bsp_search_point(render->map->bsp,
			vector4d_to_point2d(&render->camera->pos));
	item_queue.left = 0;
	item_queue.portal = NULL;
	item_queue.right = render->width;
	while (node)
	{
		render_sector(render, &item_queue, node);
		if (circular_queue_pop(render->queue, &item_queue) == 0)
			node = item_queue.portal->data.data.portal.tree_node_ptr;
		else
			node = NULL;
	}
}
