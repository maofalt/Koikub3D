/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured_surface.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:13:53 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/30 21:21:08 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "render_3D.h"
#include "ressources_managers.h"
#include "structures.h"
#include <assert.h>


//LOCAL UTILS


double	calc_wall_texture_repeat_factor_x(t_segment_d *segment)
{
	return (segment->data.size);
}

static double	calc_wall_texture_repeat_factor_y(t_segment_d *segment)
{
	return (fabs(segment->data.floor - segment->data.ceil));
}

static double	calc_wall_texture_offset(__attribute_maybe_unused__ t_segment_d *segment)
{
	return (0);
}


//--------------------------------------------------------------------------------------------


typedef struct s_texture_mapping_data
{
	t_segment_d	*surface;
	t_segment_d	relative_segment;
	t_segment_d	clipped_relative_segment;
	t_img_data	*texture;
	double		texture_width;
	double		texture_tiling_factor_x;
	double		texture_tiling_factor_y;
	double		u0;
	double		u1;
	t_segment_d	projected_top;
	t_segment_d	projected_bot;
	double		coef_top;
	double		coef_bot;
	double		x;
	double		top;
	double		bot;
	double		left;
	double		right;
	t_vector4d	world_pos;
	t_vector4d	normal;
	double		depth;
	int			img_x;
}				t_texture_mapping_data;



static inline void	calc_u(t_texture_mapping_data *data)
{
	double		relative_segment_width;
	const int	use_y = (fabs(data->clipped_relative_segment.point_b.x
				- data->clipped_relative_segment.point_a.x)
			<= fabs(data->relative_segment.point_a.y
				- data->relative_segment.point_b.y));

	relative_segment_width = data->relative_segment.point_b.vec[use_y]
		- data->relative_segment.point_a.vec[use_y];
	data->u0 = ((data->clipped_relative_segment.point_a.vec[use_y]
				- data->relative_segment.point_a.vec[use_y])
			* data->texture_width
			* data->texture_tiling_factor_x)
		/ relative_segment_width;
	data->u1 = ((data->clipped_relative_segment.point_b.vec[use_y]
				- data->relative_segment.point_a.vec[use_y])
			* data->texture_width
			* data->texture_tiling_factor_x)
		/ relative_segment_width;


	data->u0 += calc_wall_texture_offset(data->surface) * data->texture_width;
	data->u1 += calc_wall_texture_offset(data->surface) * data->texture_width;
}


static int	_set_texture_mapping_data(t_texture_mapping_data *data,
		t_3d_render *render, t_segment_d *surface)
{
	data->surface = surface;
	data->texture = texture_get_frame(surface->data.data.wall.texture.texture);
	data->texture_width
		= texture_get_frame(surface->data.data.wall.texture.texture)->size.x;
	data->texture_tiling_factor_x = calc_wall_texture_repeat_factor_x(surface);
	data->texture_tiling_factor_y = calc_wall_texture_repeat_factor_y(surface);
	data->relative_segment
		= transform_camera_relative_segment(*surface, render->camera);
	data->clipped_relative_segment = data->relative_segment;
	if (relative_segment_clip_front(&data->clipped_relative_segment))
		return (1);
	calc_u(data);
	if (project_wall(render, surface,
			&data->projected_top, &data->projected_bot))
		return (1);
	data->coef_bot = calc_segment_coef(&data->projected_bot);
	data->coef_top = calc_segment_coef(&data->projected_top);
	data->left = fmax(data->projected_top.point_a.x, data->left);
	data->right = fmin(data->projected_top.point_b.x, data->right);
	data->projected_top.point_a.y += data->coef_top
		* (data->left - data->projected_top.point_a.x);
	data->projected_top.point_b.y += data->coef_top
		* (data->right - data->projected_top.point_b.x);
	data->projected_bot.point_a.y += data->coef_bot
		* (data->left - data->projected_bot.point_a.x);
	data->projected_bot.point_b.y += data->coef_bot
		* (data->right - data->projected_bot.point_b.x);
	data->normal = surface->data.normal;
	return (0);
}


static inline void draw_vertical_line_tiled(t_3d_render *render, t_texture_mapping_data *data, int screen_x, int top)
{
	uint32_t *img = (void *)data->texture->addr;
	int offset;
	int offset_img;
	double y = 0;

	double full_project_height = data->bot - top;
	data->img_x = data->img_x % data->texture->size.x;
	double factor = ((double)data->texture->size.y * data->texture_tiling_factor_y) / (double)(data->bot - top);
	y = (int)fmax(0, render->top_array[screen_x] - top);
	double screen_bottom = fmin(render->bottom_array[screen_x], data->bot);

	while ((top + y) < screen_bottom)
	{

		if ((y + top) >= render->height || screen_x >= render->width || screen_x < 0)
			return;

		offset = (top + y) * render->width + screen_x;

		offset_img = (((int)(factor * y) % data->texture->size.y) * data->texture->size.x) + data->img_x;

		double z_pos_factor = (y) / (double)(full_project_height);
		data->world_pos.z = (data->surface->data.ceil * (1 - z_pos_factor) + data->surface->data.floor * (z_pos_factor));

		render->buffers.color[offset].d = img[offset_img];
		render->buffers.depth[offset] = data->depth;
		render->buffers.world_pos[offset] = data->world_pos;
		render->buffers.normal[offset] = data->normal;
		++y;
	}
}


static void _draw_column(t_texture_mapping_data *data, t_3d_render *render)
{
	const double alpha = (data->x - data->projected_top.point_a.x) / (data->projected_top.point_b.x - data->projected_top.point_a.x);
	const double one_over_z = (1 - alpha) / data->clipped_relative_segment.point_a.y + alpha / data->clipped_relative_segment.point_b.y;
	const double relative_x = (((1 - alpha) * (data->clipped_relative_segment.point_a.x / data->clipped_relative_segment.point_a.y) + alpha * (data->clipped_relative_segment.point_b.x / data->clipped_relative_segment.point_b.y))) / one_over_z;
	const double relative_y = 1 / one_over_z;
	double txtx;
	data->world_pos = (t_vector4d){{relative_x, relative_y, 0, 0}};
	data->world_pos = reverse_transform_camera_relative_point(data->world_pos, render->camera);

	txtx = (((1 - alpha) * (data->u0 / data->clipped_relative_segment.point_a.y) + alpha * (data->u1 / data->clipped_relative_segment.point_b.y))) / one_over_z;
	txtx = fmin(fmod(txtx, data->texture_width), data->texture_width);
	data->img_x = txtx;
	data->depth = relative_y;

	draw_vertical_line_tiled(render, data, data->x, data->top);
}




static void	_draw_surface(t_texture_mapping_data *data, t_3d_render *render)
{
	data->top = data->projected_top.point_a.y;
	data->bot = data->projected_bot.point_a.y;
	data->x = data->left;

	while ((int)data->x < (int)(data->right))
	{
		_draw_column(data, render);
		data->top += data->coef_top;
		data->bot += data->coef_bot;
		data->x += 1;
	}
}


void	draw_textured_surface(t_3d_render *render, t_segment_d *surface,
		double left, double right)
{
	t_texture_mapping_data	data;

	data.left = left;
	data.right = right;
	if (_set_texture_mapping_data(&data, render, surface))
		return ;
	_draw_surface(&data, render);
}
