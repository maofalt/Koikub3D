/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_billboard_3d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:13:53 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/09 07:42:31 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "render_3D.h"
#include "ressources_managers.h"
#include "structures.h"
#include "maths_utils.h"
#include <assert.h>

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

static int	_set_texture_mapping_data(
	t_texture_mapping_data *data,
	t_3d_render *render,
	t_segment_d *surface
	)
{
	data->texture_tiling_factor_x = 1;
	data->texture_tiling_factor_y = 1;
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

int	pixel_put_transparent(t_color *dest, t_color *src)
{
	double alpha;

	if (src->a == 255)
		return (255);
	if (src->a == 0)
	{
		dest->d = src->d;
		return (0);
	}
	alpha = (double)src->a / 255.0;
	dest->r = (1 - alpha) * (double)src->r + alpha * (double)dest->r;
	dest->g = (1 - alpha) * (double)src->g + alpha * (double)dest->g;
	dest->b = (1 - alpha) * (double)src->b + alpha * (double)dest->b;
	dest->a = 255;
	return (src->a);
}

static inline void	draw_vertical_line_tiled(
	t_3d_render *render,
	t_texture_mapping_data *data,
	int screen_x,
	int top
	)
{
	int				offset;
	int				offset_img;
	double			y;
	const double	factor = ((double)data->texture->size.y
			* data->texture_tiling_factor_y) / (double)(data->bot - top);
	const double	screen_bot
		= fmin(render->height, data->bot);

	data->img_x = data->img_x % data->texture->size.x;
	y = (int)fmax(0, 0 - top);
	while ((top + y) < screen_bot)
	{
		offset = (top + y) * render->width + screen_x;
		offset_img = (((int)(factor * y) % data->texture->size.y)
				* data->texture->size.x) + data->img_x;
		data->world_pos.z = lerp(y / (data->bot - top),
				data->surface->data.ceil, data->surface->data.floor);
		if ((data->depth < render->buffers.depth[offset]
				|| render->buffers.depth[offset] == 0)
			&& pixel_put_transparent(&render->buffers.color[offset],
				&((t_color *)data->texture->addr)[offset_img]) != 255)
		{

			render->buffers.depth[offset] = data->depth;
			render->buffers.world_pos[offset] = data->world_pos;
			render->buffers.normal[offset] = data->normal;
		}
		++y;
	}
}

static void	_draw_column(t_texture_mapping_data *data, t_3d_render *render)
{
	double	alpha;
	double	one_over_z;
	double	relative_x;
	double	relative_y;
	double	txtx;

	alpha = (data->x - data->projected_top.point_a.x)
		/ (data->projected_top.point_b.x - data->projected_top.point_a.x);
	one_over_z = lerp(alpha, 1 / data->clipped_relative_segment.point_a.y,
			1 / data->clipped_relative_segment.point_b.y);
	relative_y = 1 / one_over_z;
	relative_x = lerp(alpha, (data->clipped_relative_segment.point_a.x
				/ data->clipped_relative_segment.point_a.y),
			(data->clipped_relative_segment.point_b.x
				/ data->clipped_relative_segment.point_b.y)) * relative_y;
	data->world_pos = (t_vector4d){{relative_x, relative_y, 0, 0}};
	data->world_pos = reverse_transform_camera_relative_point(data->world_pos,
			render->camera);
	txtx = lerp(alpha, data->u0 / data->clipped_relative_segment.point_a.y,
			data->u1 / data->clipped_relative_segment.point_b.y) * relative_y;
	txtx = fmin(fmod(txtx, data->texture_width), data->texture_width);
	data->img_x = txtx;
	data->depth = relative_y;
	draw_vertical_line_tiled(render, data, data->x, data->top);
}

void	draw_billboard_3d(
		t_3d_render *render,
		t_segment_d *surface
		)
{
	t_texture_mapping_data	data;

	data.left = 0;
	data.right = render->width;
	data.surface = surface;
	data.texture = texture_get_frame(surface->data.data.wall.texture.texture);
	data.texture_width
		= texture_get_frame(surface->data.data.wall.texture.texture)->size.x;
	if (_set_texture_mapping_data(&data, render, surface))
		return ;
	data.top = data.projected_top.point_a.y;
	data.bot = data.projected_bot.point_a.y;
	data.x = data.left;
	while ((int)data.x < (int)(data.right))
	{
		_draw_column(&data, render);
		data.top += data.coef_top;
		data.bot += data.coef_bot;
		data.x += 1;
	}
}
