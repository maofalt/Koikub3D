/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_diagonals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:21:17 by motero            #+#    #+#             */
/*   Updated: 2023/10/14 21:20:58 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_to_edges.h"

bool	check_diagonal_left(t_edge_exploration_context *context,
		t_vector4d *coord)
{
	if (check_if_diagonal_left_splits_vertical_wall(context, coord)
		|| check_if_diagonal_left_splits_horizontal_wall(context, coord))
		return (true);
	return (false);
}

bool	check_if_diagonal_left_splits_vertical_wall(t_edge_exploration_context *context,
		t_vector4d *coord)
{
	const t_point2d	below_current = (t_point2d){{coord->x, coord->y + 1}};
	const t_point2d	above_current = (t_point2d){{coord->x, coord->y - 1}};
	const t_point2d	left_of_next = (t_point2d){{coord->x - 2, coord->y +1}};
	const t_point2d	next_point = (t_point2d){{coord->x - 1, coord->y + 1}};

	if ((context->visited[(int)below_current.y][(int)below_current.x] & (RIGHT | DOWN)) == (RIGHT | DOWN) &&
		(context->visited[(int)above_current.y][(int)above_current.x] & DOWN) &&
		(context->visited[(int)coord->y][(int)coord->x] & DOWN))
		return (true);
	if ((context->visited[(int)below_current.y][(int)below_current.x] & (RIGHT | DOWN)) == (RIGHT | DOWN) &&
		(context->visited[(int)left_of_next.y][(int)left_of_next.x] & RIGHT) &&
		(context->visited[(int)next_point.y][(int)next_point.x] & RIGHT))
		return (true);
	return (false);
}

bool	check_if_diagonal_left_splits_horizontal_wall(t_edge_exploration_context *context,
		t_vector4d *coord)
{
	const t_point2d	left_of_current = (t_point2d){{coord->x - 1, coord->y}};
	const t_point2d	next_point = (t_point2d){{coord->x - 1, coord->y + 1}};
	const t_point2d	below_next = (t_point2d){{next_point.x, next_point.y + 1}};
	const t_point2d	right_of_current = (t_point2d){{coord->x + 1, coord->y}};
	if ((context->visited[(int)left_of_current.y][(int)left_of_current.x] & (RIGHT | DOWN)) == (RIGHT | DOWN) &&
		(context->visited[(int)next_point.y][(int)next_point.x] & DOWN) &&
		(context->visited[(int)below_next.y][(int)below_next.x] & DOWN))
		return (true);
	if ((context->visited[(int)left_of_current.y][(int)left_of_current.x] & (RIGHT | DOWN)) == (RIGHT | DOWN) &&
		(context->visited[(int)coord->y][(int)coord->x] & RIGHT) &&
		(context->visited[(int)right_of_current.y][(int)right_of_current.x] & RIGHT))
		return (true);
	return (false);
}

bool	check_diagonal_right(t_edge_exploration_context *context, t_vector4d *coord)
{
	const t_point2d	next_point = (t_point2d){{coord->x + 1, coord->y + 1}};
	const t_point2d	below_current = (t_point2d){{coord->x, coord->y + 1}};
	const t_point2d	right_of_current = (t_point2d){{coord->x + 1, coord->y}};
	const t_point2d	above_next = (t_point2d){{next_point.x, next_point.y - 1}};
	const t_point2d	right_of_next = (t_point2d){{next_point.x + 1, next_point.y}};
	if ((context->visited[(int)right_of_current.y][(int)right_of_current.x] & (RIGHT | DOWN)) == (RIGHT | DOWN) &&
		(context->visited[(int)above_next.y][(int)above_next.x] & DOWN) &&
		(context->visited[(int)next_point.y][(int)next_point.x] & DOWN))
		return (true);
	if ((context->visited[(int)below_current.y][(int)below_current.x] & (RIGHT | DOWN)) == (RIGHT | DOWN) &&
		(context->visited[(int)right_of_next.y][(int)right_of_next.x] & RIGHT) &&
		(context->visited[(int)next_point.y][(int)next_point.x] & RIGHT))
		return (true);
	return (false);
}
