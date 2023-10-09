/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_edges.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:21:17 by motero            #+#    #+#             */
/*   Updated: 2023/10/09 18:29:53 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "map_to_edges.h"

void	explore_edge(t_edge_exploration_context *context)
{
	t_point2d		*coord;
	t_point2d		*delta;
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
    {
		return ;
    }


	context->visited[(int)coord->y][(int)coord->x] |= context->direction;
	segment->point_b.x = coord->x;
	segment->point_b.y = coord->y;
// Preventing diagonal exploration from intersections:
	if (context->direction == DIAGONAL_LEFT)
	{
	    t_point2d intersection;
	    t_point2d point_adjacent_to_intersection;
	    t_point2d next_point = {.vec = {coord->x - 1, coord->y + 1}};
	
	    // Check for intersection to the left
	    intersection = (t_point2d){coord->x - 1.0, coord->y};
	    point_adjacent_to_intersection = (t_point2d){intersection.x, intersection.y + 1};
	    if ((context->visited[(int)intersection.y][(int)intersection.x] & (RIGHT | DOWN)) == (RIGHT | DOWN) &&
	        context->map[(int)point_adjacent_to_intersection.y][(int)point_adjacent_to_intersection.x] == context->map[(int)next_point.y][(int)next_point.x])
	    {
	        return;
	    }
	
	    // Check for intersection below
	    intersection = (t_point2d){coord->x, coord->y + 1};
	    point_adjacent_to_intersection = (t_point2d){intersection.x - 1, intersection.y};
	    if ((context->visited[(int)intersection.y][(int)intersection.x] & (RIGHT | DOWN)) == (RIGHT | DOWN) &&
	        context->map[(int)point_adjacent_to_intersection.y][(int)point_adjacent_to_intersection.x] == context->map[(int)next_point.y][(int)next_point.x])
	    {
	        printf("intersection Left below\n");
			printf("\tStarting coord (%f, %f) = [%c]\n", context->current_coord.x, context->current_coord.y, context->map[(int)context->current_coord.y][(int)context->current_coord.x]);
			printf("\tCurrent coord (%f, %f) = [%c]\n", coord->x, coord->y, context->map[(int)coord->y][(int)coord->x]);
			printf("\tNext coord (%f, %f)= [%c]\n", next_point.x, next_point.y, context->map[(int)next_point.y][(int)next_point.x]);
			printf("\tIntersection coord (%f, %f) = [%c]\n", intersection.x, intersection.y, context->map[(int)intersection.y][(int)intersection.x]);
			return;
	    }
	}
	else if (context->direction == DIAGONAL_RIGHT)
	{
	    t_point2d intersection;
	    t_point2d point_adjacent_to_intersection;
	    t_point2d next_point = {.vec = {coord->x + 1, coord->y + 1}};
	
	    // Check for intersection to the right
	    intersection = (t_point2d){coord->x + 1, coord->y};
	    point_adjacent_to_intersection = (t_point2d){intersection.x, intersection.y + 1};
	    if ((context->visited[(int)intersection.y][(int)intersection.x] & (RIGHT | DOWN)) == (RIGHT | DOWN) &&
	        context->map[(int)point_adjacent_to_intersection.y][(int)point_adjacent_to_intersection.x] == context->map[(int)next_point.y][(int)next_point.x])
	    {
	        return;
	    }
	
	    // Check for intersection below
	    intersection = (t_point2d){coord->x, coord->y + 1};
	    point_adjacent_to_intersection = (t_point2d){intersection.x + 1, intersection.y};
	    if ((context->visited[(int)intersection.y][(int)intersection.x] & (RIGHT | DOWN)) == (RIGHT | DOWN) &&
	        context->map[(int)point_adjacent_to_intersection.y][(int)point_adjacent_to_intersection.x] == context->map[(int)next_point.y][(int)next_point.x])
	    {
	        return;
	    }
	}


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
	print_map(context.map);
	if (context.visited == NULL)
		return (1);
	if (process_map(&context, edges, height_map, width_map))
		return (1);
	//free2DArray(visited);
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

int	process_row_vertical_horizontal(t_edge_exploration_context *context, t_list **edges,
		int y, int width_map)
{
	int	x;

	x = 0;
	while (x < width_map)
	{
		context->current_coord = (t_point2d){{x, y}};
		if (context->map[y][x] == '1')
		{
			if (process_direction(context, edges, (t_point2d){{1, 0}}, RIGHT))
				return (1);
			if (process_direction(context, edges, (t_point2d){{0, 1}}, DOWN))
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
		context->current_coord = (t_point2d){{x, y}};
		if (context->map[y][x] == '1')
		{
			if (process_direction(context, edges, (t_point2d){{1, 1}},
				DIAGONAL_RIGHT))
				return (1);
			if (process_direction(context, edges, (t_point2d){{-1, 1}},
				DIAGONAL_LEFT))
				return (1);
		}
		x++;
	}
	return (0);
}

void	update_context(t_edge_exploration_context *context, t_point2d coord,
			t_point2d delta, t_direction dir)
{
	context->coord = coord;
	context->delta = delta;
	context->segment = (t_segment_d){context->coord, context->coord};
	context->direction = dir;
}
