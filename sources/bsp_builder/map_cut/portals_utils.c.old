/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 22:16:59 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/26 04:32:25 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "bsp_builder.h"
#include "structures.h"

void	insert_segment_sorted_by_x(t_list **dest_ptr, t_list *segment_node)
{
	t_list		*dest;
	t_segment_d	*new_segment;
	t_segment_d	*tmp_segment;

	dest = *dest_ptr;
	new_segment = segment_node->content;
	while (dest)
	{
		tmp_segment = dest->content;
		if (tmp_segment->point_a.y == new_segment->point_a.y
			&& new_segment->point_a.x <= tmp_segment->point_a.x)
		{
			break ;
		}
		if (tmp_segment->point_b.y == new_segment->point_a.y
			&& new_segment->point_a.x <= tmp_segment->point_b.x)
		{
			break ;
		}
		if (tmp_segment->point_a.y == new_segment->point_b.y
			&& new_segment->point_b.x <= tmp_segment->point_a.x)
		{
			break ;
		}
		if (tmp_segment->point_b.y == new_segment->point_b.y
			&& new_segment->point_b.x <= tmp_segment->point_b.x)
		{
			break ;
		}
		dest_ptr = &(*dest_ptr)->next;
		dest = *dest_ptr;
	}
	ft_lstadd_front(dest_ptr, segment_node);
}


void	insert_segment_sorted_by_y(t_list **dest_ptr, t_list *segment_node)
{
	t_list		*dest;
	t_segment_d	*new_segment;
	t_segment_d	*tmp_segment;

	dest = *dest_ptr;
	new_segment = segment_node->content;
	while (dest)
	{
		tmp_segment = dest->content;
		if (tmp_segment->point_a.x == new_segment->point_a.x
			&& new_segment->point_a.y <= tmp_segment->point_a.y)
		{
			break ;
		}
		if (tmp_segment->point_b.x == new_segment->point_a.x
			&& new_segment->point_a.y <= tmp_segment->point_b.y)
		{
			break ;
		}
		if (tmp_segment->point_a.x == new_segment->point_b.x
			&& new_segment->point_b.y <= tmp_segment->point_a.y)
		{
			break ;
		}
		if (tmp_segment->point_b.x == new_segment->point_b.x
			&& new_segment->point_b.y <= tmp_segment->point_b.y)
		{
			break ;
		}
		dest_ptr = &(*dest_ptr)->next;
		dest = *dest_ptr;
	}
	ft_lstadd_front(dest_ptr, segment_node);
}

void	sort_segment_lst(t_list	**segments, int use_horizontal_axis)
{
	t_list	*current;
	t_list	*next;
	t_list	*result;

	current = *segments;
	result = NULL;
	while (current)
	{
		next = current->next;
		if (use_horizontal_axis)
			insert_segment_sorted_by_x(&result, current);
		else
			insert_segment_sorted_by_y(&result, current);
		current = next;
	}
	*segments = result;
}



static double	get_segment_x(
	t_segment_d *segment,
	double required_y,
	double (*comparison_func)(double, double))
{
	if (segment->point_a.y == required_y && segment->point_b.y == required_y)
	{
		return (comparison_func(segment->point_a.x, segment->point_b.x));
	}
	else if (segment->point_a.y == required_y)
	{
		return (segment->point_a.x);
	}
	else
	{
		return (segment->point_b.x);
	}
}


static double	get_segment_y(
	t_segment_d *segment,
	double required_x,
	double (*comparison_func)(double, double))
{
	if (segment->point_a.x == required_x && segment->point_b.x == required_x)
	{
		return (comparison_func(segment->point_a.y, segment->point_b.y));
	}
	else if (segment->point_a.x == required_x)
	{
		return (segment->point_a.y);
	}
	else
	{
		return (segment->point_b.y);
	}
}

static void	detect_gap_x(t_list *sorted_segments, double y)
{
	t_list		*current;
	double		last_pos;
	double		current_pos;
	t_segment_d	*segment;

	segment = sorted_segments->content;
	last_pos = get_segment_x(segment, y, fmax);
	current = sorted_segments->next;
	y = 0;
	while (current)
	{
		segment = current->content;
		current_pos = get_segment_x(segment, y, fmin);

		if (current_pos > last_pos)
		{
			//gap
			printf("portal_x = y:%f;x: %f , %f\n", y, last_pos, current_pos);
		}
		last_pos = fmax(segment->point_a.x,
				segment->point_b.x);
		current = current->next;
	}
	printf("detect_gap_x\n");
}


// double	get_segment_y(t_segment_d	*segment, double required_x)
// {
// 	if (segment->point_a.x == segment->point_b.x)
// 	{
// 		return (fmin(segment->point_a.y, segment->point_b.y));
// 	}
// 	if (segment->point_a.x == required_x)
// 	{
// 		return (segment->point_a.y);
// 	}
// 	return (segment->point_b.y);
// }

static void	detect_gap_y(t_list *sorted_segments, double x)
{
	t_list		*current;
	double		last_pos;
	double		current_pos;
	t_segment_d	*segment;

	segment = sorted_segments->content;
	last_pos = get_segment_y(segment, x, fmax);
	current = sorted_segments->next;
	x = 0;
	while (current)
	{
		segment = current->content;
		current_pos = get_segment_y(segment, x, fmin);

		if (current_pos > last_pos)
		{
			//gap
			printf("portal_y = x:%f;y: %f , %f\n", x, last_pos, current_pos);
		}
		last_pos = fmax(segment->point_a.y,
				segment->point_b.y);
		current = current->next;
	}
	printf("detect_gap_y\n");
}


static int	is_segment_horizontal(t_segment_d *segment)
{
	return (segment->point_a.x == segment->point_b.x);
}


int	detect_gap(t_list **segments, t_segment_d *separator)
{
	const int use_horizontal_axis = !is_segment_horizontal(separator);

	if (segments == NULL || *segments == NULL)
		return (0);
	sort_segment_lst(segments, use_horizontal_axis);
	if (use_horizontal_axis)
		detect_gap_x(*segments, separator->point_a.y);
	else
		detect_gap_y(*segments, separator->point_a.x);
	return (0);
}



// int    main(void)
// {
//     t_list *dest = NULL;
//     t_segment_d    seg;
//     ft_memset(&seg, 0, sizeof(t_segment_d));
//     t_list *seg_node = ft_lstnew(&seg);

//     insert_segment_sorted_by_x(&dest, seg_node);
//     printf("Heeeeeeeeeeeey\n");

//     t_segment_d    seg_2;
//     ft_memset(&seg_2, 0, sizeof(t_segment_d));
//     t_list *seg_node_2 = ft_lstnew(&seg_2);
//     seg_2.point_a.x = -1;
//     insert_segment_sorted_by_x(&dest, seg_node_2);

//     return 0;
// }
