/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_builder.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:34:36 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/05 20:32:40 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSP_BUILDER_H
# define BSP_BUILDER_H

# include "structures.h"

typedef enum e_side
{
	SIDE_ON			= 0b0000,
	SIDE_LEFT		= 0b0001,
	SIDE_RIGHT		= 0b0010,
	SIDE_INTERSECT	= 0b0011,
}	t_side;

typedef struct s_bsp_segment
{
	t_segment_d			*segment;
	int					used_as_separator;
	t_side				side_of_separator;
	t_side				point_a_side;
	t_side				point_b_side;
	int					has_separator_intersection;
	t_point2d			separator_intersection;
	t_list				*node_ptr;
}	t_bsp_segment;


void			sort_lst_node_array(t_list **arr, int size,
					int (*comparison_function)(t_list *, t_list *));

t_bsp_segment	*create_bsp_segment(t_segment_d *segment);

void			destroy_full_bsp_segment(t_bsp_segment *bsp_seg);
t_list			*convert_to_bsp_segments(t_list *segment_list);
t_list			*create_bsp_segment_node(void);
t_bsp_segment	*duplicate_bsp_segment(t_bsp_segment *original);
t_list			*duplicate_bsp_segment_node(t_list *original_node);
void			destroy_full_bsp_segment_node(t_list *node);
void			lst_move_node(t_list **list, t_list **node);

int				map_cut(t_list **bsp_segments, t_list **left, t_list **right);

int				construct_bsp(t_list **segments, t_tree_node **tree);
void			destroy_segment_tree(t_tree_node **tree);

t_point2d		find_intersection(t_segment_d line, t_segment_d seg);

int				create_portals(t_list *bsp_segments, int is_sep_horizontal, t_list **portal_lst);


void			bsp_segment_compute_intersec(
					t_bsp_segment *segment,
					t_segment_d *separator
					);

int				cut_space(
					t_list **segments,
					t_segment_d *separator,
					t_list **left,
					t_list **right);

#endif
