/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 03:57:17 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/22 22:20:45 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "structures.h"
#include "map_to_edges.h"
#include "bsp_builder.h"

int	draw_player(t_cub *data, t_canvas *canvas)
{
	t_segment_d	scaled_segment;

	scaled_segment.point_a = data->player.pos;
	scaled_segment.point_b.vec = data->player.pos.vec + data->player.dir.vec;
	scaled_segment.point_a.vec *= 10;
	scaled_segment.point_b.vec *= 10;
	draw_segment_canvas(canvas, &scaled_segment,
		(t_color){.d = 0xFFFFFFFF});
	return (0);
}

int	draw_map_with_tree(
		t_cub *data,
		t_canvas *canvas,
		t_tree_node	*tree,
		int depth)
{
	t_segment_d	separator;
	t_point2d	player_pos;
	int			player_side;
	t_color		color;

	if (!tree)
		return (0);
	player_pos = vector4d_to_point2d(&data->player.pos);
	separator = *((t_bsp_tree_node_data *)tree->data)->separator;
	player_side = point_space_partitioning(&separator, &player_pos);
	if (player_side > 0)
		draw_map_with_tree(data, canvas, tree->right, depth + 1);
	else
		draw_map_with_tree(data, canvas, tree->left, depth + 1);
	color.d = 0xFF0000FF;
	color.rgb_color /= (uint8_t)depth;
	separator.point_a.vec *= 10;
	separator.point_b.vec *= 10;
	draw_segment_canvas(canvas, &separator, color);
	return (0);
}

void	draw_player_fixed(t_canvas *canvas)
{
	t_segment_d	player;

	player.point_a.x = canvas->size.x / 2 ;
	player.point_a.y = canvas->size.y / 2 ;
	player.point_b.x = canvas->size.x / 2;
	player.point_b.y = canvas->size.y / 2 + 1;
	draw_segment_canvas(canvas, &player,
		(t_color){.d = 0xFFFF0000});
}



//----------------------------------

t_segment_d	transform_player_relative(t_segment_d segment, t_player player)
{
	t_segment_d	relative_segment;

	segment.point_a.vec = segment.point_a.vec - player.pos.vec;
	segment.point_b.vec = segment.point_b.vec - player.pos.vec;
	relative_segment.point_a.x = segment.point_a.x * player.dir.y - segment.point_a.y * player.dir.x;
	relative_segment.point_a.y = segment.point_a.x * player.dir.x + segment.point_a.y * player.dir.y;
	relative_segment.point_b.x = segment.point_b.x * player.dir.y - segment.point_b.y * player.dir.x;
	relative_segment.point_b.y = segment.point_b.x * player.dir.x + segment.point_b.y * player.dir.y;

	return (relative_segment);
}

t_segment_d	transform_perspective(t_segment_d segment)
{
	t_segment_d	perspective_segment;

	perspective_segment.point_a.x = -segment.point_a.x * 16 / segment.point_a.y;
	perspective_segment.point_a.y = segment.point_a.z / segment.point_a.y;
	perspective_segment.point_b.x = -segment.point_b.x * 16 / segment.point_b.y;
	perspective_segment.point_b.y = segment.point_b.z / segment.point_b.y;

	return (perspective_segment);
}

void	draw_wall(t_cub *data, t_canvas *canvas, t_segment_d wall)
{
	t_segment_d	projection_bottom;
	t_segment_d	projection_top;
	t_segment_d	player_right;
	t_vector4d	intersect;

	player_right.point_a.x = 0;
	player_right.point_a.y = 0;
	player_right.point_a.x = 10;
	player_right.point_a.y = 0.01;
	wall = transform_player_relative(wall, data->player);

	if (wall.point_a.y <= 0 && wall.point_b.y <= 0)
		return ;
	if (wall.point_a.y <= 0.01 || wall.point_b.y <= 0.01)
	{
		intersect = point2d_to_vector4d_cpy(find_intersection(player_right, wall)); //TODO replace by more specialized function
		intersect.y = 0.01;
		if (wall.point_a.y < 0.01)
		{
			intersect.z = wall.point_a.z;
			wall.point_a = intersect;
		}
		if (wall.point_b.y < 0.01)
		{
			intersect.z = wall.point_b.z;
			wall.point_b = intersect;
		}
	}
	wall.point_a.z = 10;
	wall.point_b.z = 10;
	projection_top = transform_perspective(wall);
	wall.point_a.z = -10;
	wall.point_b.z = -10;
	projection_bottom = transform_perspective(wall);
}

//----------------------------------
void	game_render(t_cub *data)
{
	t_canvas	*canvas;

	canvas = get_canvas_from_list(data->canvas_list, MAP);
	fill_canvas(
		canvas,
		(t_color){.d = 0xFF000000});
	// draw_map(data, canvas);
	draw_player(data, canvas);
	// draw_map_perspective_test(data, canvas);
	draw_map_with_tree(data, canvas, data->map_data.bsp, 1);
	draw_player_fixed(canvas);
	canvas_to_mlx_image(data->screen,
		canvas);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->screen.mlx_img, 0, 0);
}

