/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 22:16:59 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/25 23:58:30 by olimarti         ###   ########.fr       */
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

static void	detect_gap_x(t_list *sorted_segments)
{
	t_list	*current;
	double	last_pos;
	double	current_pos;

	last_pos = fmax(((t_segment_d *)sorted_segments->content)->point_a.x,
			((t_segment_d *)sorted_segments->content)->point_b.x);
	current = sorted_segments->next;
	while (current)
	{
		current_pos = fmax(((t_segment_d *)current->content)->point_a.x,
				((t_segment_d *)current->content)->point_b.x);

		if (current_pos > last_pos)
		{
			//gap
			printf("portal_x = %f , %f\n", last_pos, current_pos);
		}
		last_pos = current_pos;
		current = current->next;
	}
	printf("detect_gap_x\n");
}

static void	detect_gap_y(t_list *sorted_segments)
{
	t_list	*current;
	double	last_pos;
	double	current_pos;

	last_pos = fmax(((t_segment_d *)sorted_segments->content)->point_a.y,
			((t_segment_d *)sorted_segments->content)->point_b.y);
	current = sorted_segments->next;
	while (current)
	{
		current_pos = fmin(((t_segment_d *)current->content)->point_a.y,
				((t_segment_d *)current->content)->point_b.y);

		if (current_pos > last_pos)
		{
			//gap
			printf("portal_y = %f , %f\n", last_pos, current_pos);
		}
		last_pos = fmax(((t_segment_d *)current->content)->point_a.y,
				((t_segment_d *)current->content)->point_b.y);
		current = current->next;
	}
	printf("detect_gap_y\n");
}


int	detect_gap(t_list *sorted_segments, int use_horizontal_axis)
{

	if (use_horizontal_axis)
		detect_gap_x(sorted_segments);
	else
		detect_gap_y(sorted_segments);
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
