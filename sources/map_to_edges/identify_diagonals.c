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

bool    check_diagonal_left(t_edge_exploration_context *context, t_point2d *coord)
{
    t_point2d next_point = (t_point2d) {{coord->x - 1, coord->y + 1}};
    t_point2d below_next = (t_point2d) {{next_point.x, next_point.y + 1}};
    t_point2d below_current = (t_point2d) {{coord->x, coord->y + 1}};
    t_point2d right_of_current = (t_point2d){{coord->x + 1, coord->y}};
    t_point2d left_of_current = (t_point2d){{coord->x - 1, coord->y}};
    t_point2d above_current = (t_point2d) {{coord->x, coord->y - 1}};
    t_point2d left_of_next = (t_point2d) {{next_point.x - 1, next_point.y}};

    // Check for "cutting through" a vertical wall
    if ((context->visited[(int)below_current.y][(int)below_current.x] & (RIGHT | DOWN)) == (RIGHT | DOWN) &&
        (context->visited[(int)above_current.y][(int)above_current.x] & DOWN) &&
        (context->visited[(int)coord->y][(int)coord->x] & DOWN))
    {
        return true;
    }

    if ((context->visited[(int)left_of_current.y][(int)left_of_current.x] & (RIGHT | DOWN)) == (RIGHT | DOWN) &&
        (context->visited[(int)next_point.y][(int)next_point.x] & DOWN) &&
        (context->visited[(int)below_next.y][(int)below_next.x] & DOWN))
    {
        return true;
    }

    // Check for "cutting through" a horizontal wall
    if ((context->visited[(int)below_current.y][(int)below_current.x] & (RIGHT | DOWN)) == (RIGHT | DOWN) &&
        (context->visited[(int)left_of_next.y][(int)left_of_next.x] & RIGHT) &&
        (context->visited[(int)next_point.y][(int)next_point.x] & RIGHT))
    {
        return true;
    }

    if ((context->visited[(int)left_of_current.y][(int)left_of_current.x] & (RIGHT | DOWN)) == (RIGHT | DOWN) &&
        (context->visited[(int)coord->y][(int)coord->x] & RIGHT) &&
        (context->visited[(int)right_of_current.y][(int)right_of_current.x] & RIGHT))
    {
        return true;
    }
    return false;
}

bool    check_diagonal_right(t_edge_exploration_context *context, t_point2d *coord)
{
    t_point2d next_point = (t_point2d){{coord->x + 1, coord->y + 1}};
    t_point2d below_current = (t_point2d){{coord->x, coord->y + 1}};
    t_point2d right_of_current = (t_point2d){{coord->x + 1, coord->y}};
    t_point2d above_next = (t_point2d){{next_point.x, next_point.y - 1}};
    t_point2d right_of_next = (t_point2d){{next_point.x + 1, next_point.y}};

    // Check for "cutting through" a vertical wall
    if ((context->visited[(int)right_of_current.y][(int)right_of_current.x] & (RIGHT | DOWN)) == (RIGHT | DOWN) &&
        (context->visited[(int)above_next.y][(int)above_next.x] & DOWN) &&
        (context->visited[(int)next_point.y][(int)next_point.x] & DOWN))
    {
        return true;
    }

    // Check for "cutting through" a horizontal wall
    if ((context->visited[(int)below_current.y][(int)below_current.x] & (RIGHT | DOWN)) == (RIGHT | DOWN) &&
        (context->visited[(int)right_of_next.y][(int)right_of_next.x] & RIGHT) &&
        (context->visited[(int)next_point.y][(int)next_point.x] & RIGHT))
    {
        return true;
    }

    return false;
}