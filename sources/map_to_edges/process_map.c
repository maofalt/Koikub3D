/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:21:17 by motero            #+#    #+#             */
/*   Updated: 2024/02/27 02:04:40 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_to_edges.h"

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
