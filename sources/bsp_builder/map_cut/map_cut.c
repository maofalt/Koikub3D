/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:04:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/14 20:31:09 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "bsp_builder.h"
#include "structures.h"

typedef struct s_space_cut_context{
	t_list			**segments;
	t_list			*segment_node;
	t_segment_d		segment_cpy;
	t_segment_d		*separator;
	t_list			**left;
	t_list			**right;
	int				point_a_side;
	int				point_b_side;
	t_point2d		intersection;
	int				err;
}	t_space_cut_context;

static int	_cut_segment(t_space_cut_context *context)
{
	int			err;
	t_vector4d	tmp;

	context->intersection
		= find_intersection(*context->separator, context->segment_cpy);
	tmp = point2d_to_vector4d(&context->intersection);
	if (context->point_a_side < 0)
	{
		((t_segment_d *)context->segment_node->content)->point_b
			= tmp;
		lst_move_node(context->left, &context->segment_node);
	}
	else if (context->point_a_side > 0)
	{
		*((t_segment_d *)context->segment_node->content) = (t_segment_d)
		{tmp, context->segment_cpy.point_a, context->segment_cpy.data};
		lst_move_node(context->right, &context->segment_node);
	}
	if (context->point_b_side < 0)
		err = add_segment_to_lst(context->left, (t_segment_d)
			{context->segment_cpy.point_b, tmp, context->segment_cpy.data});
	else
		err = add_segment_to_lst(context->right, (t_segment_d)
			{tmp, context->segment_cpy.point_b, context->segment_cpy.data});
	return (err);
}

static void	_no_segment_intersection(t_space_cut_context *context)
{
	if (context->point_a_side < 0 || context->point_b_side < 0)
		lst_move_node(context->left, &context->segment_node);
	else
		lst_move_node(context->right, &context->segment_node);
}

static t_space_cut_context	_context_init(
	t_list **segments,
	t_segment_d *separator,
	t_list **left,
	t_list **right)
{
	t_space_cut_context	context;

	*left = NULL;
	*right = NULL;
	context.segment_node = *segments;
	*segments = NULL;
	context.segments = segments;
	context.separator = separator;
	context.left = left;
	context.right = right;
	return (context);
}

// Divide a 2D space using a line.
// Return 0 if successful, or 1 if unsuccessful (due to a malloc error).
// Distribute segments to the Left and Right lists,
// and split segments that are intersected by the separator line.
// Segments lying exactly on the separator are retained in the Separator list.
int	cut_space(
	t_list **segments,
	t_segment_d *separator,
	t_list **left,
	t_list **right)
{
	t_space_cut_context	context;
	t_point2d			point;

	context = _context_init(segments, separator, left, right);
	while (context.segment_node != NULL)
	{
		context.segment_cpy = *(t_segment_d *)context.segment_node->content;
		point = vector4d_to_point2d(&context.segment_cpy.point_a);
		context.point_a_side = point_space_partitioning(separator, &point);
		point = vector4d_to_point2d(&context.segment_cpy.point_b);
		context.point_b_side = point_space_partitioning(separator, &point);
		if ((context.point_a_side | context.point_b_side) == 0)
		{
			lst_move_node(segments, &context.segment_node);
			continue ;
		}
		else if (context.point_a_side * context.point_b_side < 0)
		{
			if (_cut_segment(&context))
				return (1);
		}
		else
			_no_segment_intersection(&context);
	}
	return (0);
}
