/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 03:57:17 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/20 10:30:57 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "engine.h"
#include "map_to_edges.h"
#include "bsp_builder.h"
// #include "bsp_builder.h"

// void	fill_image(t_img_data *image, int color)
// {
// 	char				*px;
// 	unsigned long long	image_size;

// 	px = image->addr;
// 	image_size = image->line_len * image->size[1] / image->bpp * 8;
// 	while (image_size > 0)
// 	{
// 		*(unsigned int *)px = color;
// 		px += image->bpp >> 3;
// 		image_size --;
// 	}
// }


// int	draw_player(t_cub *data, t_canvas *canvas)
// {
// 	t_segment_d	scaled_segment;

// 	scaled_segment.point_a = data->player.pos;
// 	scaled_segment.point_b.vec = data->player.pos.vec + data->player.dir.vec;
// 	scaled_segment.point_a.vec *= 10;
// 	scaled_segment.point_b.vec *= 10;
// 	// draw_segment(&data->screen, &scaled_segment,
// 		// 0xFFFFFFFF);
// 	draw_segment_canvas(canvas, &scaled_segment,
// 			(t_color) {.d = 0xFFFFFFFF});
// 	return (0);
// }

// int	draw_map(t_list *segments_lst, t_canvas *canvas)
// {
// 	t_segment_d	scaled_segment;

// 	while (segments_lst != NULL)
// 	{
// 		scaled_segment = *(t_segment_d *)segments_lst->content;
// 		scaled_segment.point_a.vec *= 10;
// 		scaled_segment.point_b.vec *= 10;
// 		draw_segment_canvas(canvas, &scaled_segment,
// 			(t_color) {.d = (size_t)(void *)segments_lst});
// 		segments_lst = segments_lst->next;
// 	}
// 	return (0);
// }


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

// int	find_player_node(t_cub *data, t_tree_node	*tree)
// {
// 	t_segment_d	*separator;
// 	t_point2d	player_pos;
// 	int			player_side;

// 	player_pos = vector4d_to_point2d(&data->player.pos);
// 	while (tree != NULL)
// 	{
// 		separator = ((t_bsp_tree_node_data *)tree->data)->separator;
// 		player_side = point_space_partitioning(separator, &player_pos);
// 		if (player_side > 0)
// 		{
// 			tree = tree->right;
// 		}
// 		else
// 		{
// 			tree = tree->left;
// 		}
// 	}
// 	return (tree);
// }


int	draw_map_seg(t_list *segments_lst, t_canvas *canvas)
{
	t_segment_d	scaled_segment;

	while (segments_lst != NULL)
	{
		scaled_segment = *(t_segment_d *)segments_lst->content;
		scaled_segment.point_a.vec *= 10;
		scaled_segment.point_b.vec *= 10;
		draw_segment_canvas(canvas, &scaled_segment,
			(t_color) {.d = 0xFF555555});
		segments_lst = segments_lst->next;
	}
	return (0);
}

int	draw_map_with_tree(t_cub *data, t_canvas *canvas, t_tree_node	*tree,	int depth)
{
	t_segment_d	separator;
	t_point2d	player_pos;
	int			player_side;

	if (!tree)
		return (0);
	player_pos = vector4d_to_point2d(&data->player.pos);
	separator = *((t_bsp_tree_node_data *)tree->data)->separator;
	player_side = point_space_partitioning(&separator, &player_pos);
	if (player_side > 0)
	{
		draw_map_with_tree(data, canvas, tree->right, depth + 1);
	}
	else
	{
		draw_map_with_tree(data, canvas, tree->left, depth + 1);
	}
	// if (player_side > 0)
	// {
	// 	draw_map_with_tree(data, canvas, tree->left);
	// }
	// else
	// {
	// 	draw_map_with_tree(data, canvas, tree->right);
	// }
	t_color color;

	color.d = 0xFF0000FF;
	color.d |= (tree->left == NULL) *  0x0000FF00;
	color.d |= (tree->right == NULL) * 0x00FF0000;
	color.r /= depth;
	color.g /= depth;
	color.b /= depth;
	color.a /= depth;
	separator.point_a.vec *= 10;
	separator.point_b.vec *= 10;
	draw_segment_canvas(canvas, &separator, color);
	return (0);
}



int	draw_map(t_cub *data, t_canvas *canvas)
{
	// t_segment_d	scaled_segment;
	t_list		*segments_lst;
	t_tree_node	*tree;

	tree = NULL;
	if (data->win_ptr == NULL)
		return (1);
	segments_lst = NULL;
	if (extract_edge_recursively(data->map, &segments_lst))
		return (1);
	draw_map_seg(segments_lst, canvas);
	construct_bsp(&segments_lst, &tree, data);
	draw_map_with_tree(data, canvas, tree, 1);
	// while (segments_lst != NULL)
	// {
	// 	scaled_segment = *(t_segment_d *)segments_lst->content;
	// 	scaled_segment.point_a.vec *= 10;
	// 	scaled_segment.point_b.vec *= 10;
	// 	draw_segment_canvas(canvas, &scaled_segment,
	// 		(t_color){.d = (size_t)(void *)segments_lst});
	// 	segments_lst = segments_lst->next;
	// }
	ft_lstclear(&segments_lst, free);
	return (0);
}

t_point2d gpt_relative_point_to_player(t_point2d point, t_player player)
{
    // Translate so the player is at the origin
    point.x -= player.pos.x;
    point.y -= player.pos.y;

    // Calculate the angle between player's direction and positive X-axis
    double angle = atan2(player.dir.y, player.dir.x);

    // Rotate the point around the player to align with the desired view
    t_point2d relative_point;
    relative_point.y = point.x * cos(-angle) - point.y * sin(-angle);
    relative_point.x = point.x * sin(-angle) + point.y * cos(-angle);

    // Translate back to screen center
    // relative_point.x += screen_center.x;
    // relative_point.y += screen_center.y;

    return relative_point;
}



int	draw_map_fixed_player(t_cub *data, t_canvas *canvas)
{
	// t_segment_d	scaled_segment;
	t_list		*segments_lst;
	t_segment_d	wall;
	t_segment_d	projection;
	t_point2d	projected_point;
	t_tree_node	*tree;
	t_point2d	middle;


	middle = (t_point2d){{canvas->size.x, canvas->size.y}};
	middle.vec /=2;
	tree = NULL;
	if (data->win_ptr == NULL)
		return (1);
	segments_lst = NULL;
	if (extract_edge_recursively(data->map, &segments_lst))
		return (1);
	while (segments_lst)
	{
	wall = *(t_segment_d*)segments_lst->content;
	projected_point = gpt_relative_point_to_player(vector4d_to_point2d(&wall.point_a), data->player);
	projection.point_a = point2d_to_vector4d(&projected_point);
	projected_point = gpt_relative_point_to_player(vector4d_to_point2d(&wall.point_b), data->player);
	projection.point_b = point2d_to_vector4d(&projected_point);
	projection.point_a.vec *=10;
	projection.point_b.vec *=10;
	projection.point_a.x += middle.x;
	projection.point_b.x += middle.x;
	projection.point_a.y += middle.y;
	projection.point_b.y += middle.y;
	printf("%f %f ->%f %f\n", projection.point_a.x, projection.point_a.y, projection.point_b.x, projection.point_b.y);
	draw_segment_canvas(canvas, &projection,
		(t_color) {.d = 0xFFFFFFFF});
		segments_lst = segments_lst->next;
	}
	ft_lstclear(&segments_lst, free);
	return (0);
}

void	draw_player_fixed(t_canvas *canvas)
{
	t_segment_d	player;

	player.point_a.x = canvas->size.x / 2 ;
	player.point_a.y = canvas->size.y / 2 ;
	player.point_b.x = canvas->size.x / 2;
	player.point_b.y = canvas->size.y / 2 + 10;
	draw_segment_canvas(canvas, &player,
		(t_color){.d = 0xFFFF0000});
}





// t_point2d	basic_projection_test(t_vector4d point, t_player player)
// {
// 	const double	angle = atan2(player.dir.y, player.dir.x);
// 	t_point2d relative_point;
// 	t_point2d projected;

// 	point.x -= player.pos.x;
// 	point.y -= player.pos.y;

// 	relative_point.y = point.x * cos(-angle) - point.y * sin(-angle);
// 	relative_point.x = point.x * sin(-angle) + point.y * cos(-angle);

// 	if (relative_point.y <= 0)
// 	{
// 		projected.x = -1;
// 		projected.y = -1;
// 		return (projected);
// 	}
// 	projected.x = relative_point.x / relative_point.y;
// 	projected.y = point.z / relative_point.y; // replace 0 by height

// 	return(projected);
// }



// int	draw_map_proj(t_cub *data, t_canvas *canvas)
// {
// 	// t_segment_d	scaled_segment;
// 	t_list		*segments_lst;
// 	t_segment_d	wall;
// 	t_segment_d	projection;
// 	t_point2d	projected_point;
// 	t_tree_node	*tree;
// 	t_point2d	middle;
// 	// t_point2d	right_player;


// 	// right_player.x = -data->player.dir.y;
// 	// right_player.y = data->player.dir.x;
// 	middle = (t_point2d){{canvas->size.x, canvas->size.y}};
// 	middle.vec /=2;
// 	tree = NULL;
// 	if (data->win_ptr == NULL)
// 		return (1);
// 	segments_lst = NULL;
// 	if (extract_edge_recursively(data->map, &segments_lst))
// 		return (1);
// 	while (segments_lst)
// 	{

// 	wall = *(t_segment_d*)segments_lst->content;
// 	wall.point_a.z = 10;
// 	wall.point_b.z = 10;
// 	projected_point = basic_projection_test(wall.point_a, data->player);
// 	projection.point_a = point2d_to_vector4d(&projected_point);
// 	projected_point = basic_projection_test(wall.point_b, data->player);
// 	projection.point_b = point2d_to_vector4d(&projected_point);
// 	if (projection.point_a.x != -1 && projection.point_a.x != -1)
// 	{

// 	projection.point_a.vec *=10;
// 	projection.point_b.vec *=10;
// 	projection.point_a.x += middle.x;
// 	projection.point_b.x += middle.x;
// 	projection.point_a.y += middle.y;
// 	projection.point_b.y += middle.y;
// 	printf("%f %f ->%f %f\n", projection.point_a.x, projection.point_a.y, projection.point_b.x, projection.point_b.y);
// 	draw_segment_canvas(canvas, &projection,
// 		(t_color) {.d = 0xFFFFFFFF});
// 	}
// 		segments_lst = segments_lst->next;
// 	}
// 	ft_lstclear(&segments_lst, free);
// 	return (0);
// }




void	game_update(t_cub *data)
{
	player_handle_event(data);
}


void	game_render(t_cub *data)
{

	fill_canvas(
		get_canvas_from_list(data->canvas_list, MAP),
		(t_color){.d = 0xFF000000});
	draw_map(data, get_canvas_from_list(data->canvas_list, MAP));
	draw_player(data, get_canvas_from_list(data->canvas_list, MAP));
	draw_map_fixed_player(data, get_canvas_from_list(data->canvas_list, MAP));
	// draw_map_proj(data, get_canvas_from_list(data->canvas_list, MAP));
	draw_player_fixed(get_canvas_from_list(data->canvas_list, MAP));
	canvas_to_mlx_image(data->screen,
		get_canvas_from_list(data->canvas_list, MAP));
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->screen.mlx_img, 0, 0);
}

int	render(t_cub *data)
{
	if (data->win_ptr == NULL)
		return (1);
	game_update(data);
	game_render(data);
	usleep(1);
	return (0);
}


// int	map_visualizer_draw(t_cub *data)
// {
// 	t_list			*current;

// 	(void)current;
// 	if (data->win_ptr == NULL)
// 		return (1);
// 	canvas_to_mlx_image(data->screen,
// 		get_canvas_from_list(data->canvas_list, MAP));
// 	mlx_put_image_to_window(data->mlx_ptr,
// 		data->win_ptr,
// 		data->screen.mlx_img, 0, 0);
// 	data->update = 0;
// 	usleep(10);
// 	return (0);
// }






// --------------------------



