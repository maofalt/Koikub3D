/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_edges.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:21:17 by motero            #+#    #+#             */
/*   Updated: 2023/10/14 20:30:17 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_to_edges.h"

void	explore_edge(t_edge_exploration_context *context)
{
	t_vector4d		*coord;
	t_vector4d		*delta;
	t_segment_d		*segment;

	coord = &(context->coord);
	delta = &(context->delta);
	segment = &(context->segment);
	if (coord->x < 0 || coord->y < 0)
		return ;
	if (context->map[(int)coord->y][(int)coord->x] != '1')
		return ;
	if (context->visited[(int)coord->y][(int)coord->x] & context->direction)
		return ;
	if ((context->current_coord.x == coord->x && context->current_coord.y == coord->y) &&
		context->map[(int)(coord->y + delta->y)][(int)(coord->x + delta->x)] != '1')
		return ;
	context->visited[(int)coord->y][(int)coord->x] |= context->direction;
	segment->point_b = *coord;
	if (context->direction == DIAGONAL_LEFT && check_diagonal_left(context, &(context->coord)))
		return ;
	else if (context->direction == DIAGONAL_RIGHT && check_diagonal_right(context, &(context->coord)))
		return ;
	coord->x += delta->x;
	coord->y += delta->y;
	explore_edge(context);
}

int	extract_edge_recursively(char **map, t_list **edges)
{
	t_edge_exploration_context	context;
	const int					height_map = get_map_height(map);
	const int					width_map = get_map_width(map);

	context.map = map;
	*edges = NULL;
	context.visited = malloc2DArray(map);
	if (context.visited == NULL)
		return (1);
	if (process_map(&context, edges, height_map, width_map))
		return (1);
	free2DArray(context.visited);
	printf("extracted_edge_recursively done!\n");
	return (0);
}

int	process_map(t_edge_exploration_context *context, t_list **edges,
		int height_map, int width_map)
{
	int	y;

	y = 0;
	while (y < height_map)
	{
		if (process_row_vertical_horizontal(context, edges, y, width_map))
			return (1);
		y++;
	}
	y = 0;
	while (y < height_map)
	{
		if (process_row_diagonal(context, edges, y, width_map))
			return (1);
		y++;
	}
	return (0);
}

int	process_row_vertical_horizontal(t_edge_exploration_context *context,
	t_list **edges,
	int y,
	int width_map)
{
	int	x;

	x = 0;
	while (x < width_map)
	{
		context->current_coord = (t_vector4d){{x, y, 0, 0}};
		if (context->map[y][x] == '1')
		{
			if (process_direction(context, edges,
				(t_vector4d){{1, 0, 0, 0}}, RIGHT))
				return (1);
			if (process_direction(context, edges,
				(t_vector4d){{0, 1, 0, 0}}, DOWN))
				return (1);
		}
		x++;
	}
	return (0);
}

int	process_row_diagonal(t_edge_exploration_context *context, t_list **edges,
		int y, int width_map)
{
	int	x;

	x = 0;
	while (x < width_map)
	{
		context->current_coord = (t_vector4d){{x, y, 0, 0}};
		if (context->map[y][x] == '1')
		{
			if (process_direction(context, edges, (t_vector4d){{1, 1, 0, 0}},
				DIAGONAL_RIGHT))
				return (1);
			if (process_direction(context, edges, (t_vector4d){{-1, 1, 0, 0}},
				DIAGONAL_LEFT))
				return (1);
		}
		x++;
	}
	return (0);
}

void	update_context(t_edge_exploration_context *context, t_vector4d coord,
			t_vector4d delta, t_direction dir)
{
	t_segment_data	data;

	ft_memset(&data, 0, sizeof(t_segment_data));
	context->coord = coord;
	context->delta = delta;
	context->segment = (t_segment_d){context->coord, context->coord, data};
	context->direction = dir;
}
