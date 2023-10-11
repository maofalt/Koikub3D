/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:04:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/11 02:53:29 by olimarti         ###   ########.fr       */
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
	int	err;

	context->intersection
		= find_intersection(*context->separator, context->segment_cpy);
	if (context->point_a_side < 0)
	{
		((t_segment_d *)context->segment_node->content)->point_b
			= context->intersection;
		lst_move_node(context->left, &context->segment_node);
	}
	else if (context->point_a_side > 0)
	{
		*((t_segment_d *)context->segment_node->content) = (t_segment_d)
		{context->intersection, context->segment_cpy.point_a};
		lst_move_node(context->right, &context->segment_node);
	}
	if (context->point_b_side < 0)
		err = add_segment_to_lst(context->left, (t_segment_d)
			{context->segment_cpy.point_b, context->intersection});
	else
		err = add_segment_to_lst(context->right, (t_segment_d)
			{context->intersection, context->segment_cpy.point_b});
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

int	cut_space(
	t_list **segments,
	t_segment_d *separator,
	t_list **left,
	t_list **right)
{
	t_space_cut_context	context;

	context = _context_init(segments, separator, left, right);
	while (context.segment_node != NULL)
	{
		context.segment_cpy = *(t_segment_d *)context.segment_node->content;
		context.point_a_side = point_space_partitioning(separator,
				&context.segment_cpy.point_a);
		context.point_b_side = point_space_partitioning(separator,
				&context.segment_cpy.point_b);
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
