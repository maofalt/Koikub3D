/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_builder.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:34:36 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 02:07:36 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSP_BUILDER_H
# define BSP_BUILDER_H

# include "structures.h"

typedef struct s_bsp_segment
{
	t_segment_d	*segment;
	int			used_as_separator;
	t_side		side_of_separator;
	t_side		point_a_side;
	t_side		point_b_side;
	int			has_separator_intersection;
	t_point2d	separator_intersection;
	t_list		*node_ptr;
}				t_bsp_segment;

void			sort_lst_node_array(t_list **arr, int size,
					int (*comparison_function)(t_list *, t_list *));

t_bsp_segment	*create_bsp_segment(t_segment_d *segment);
t_bsp_segment	*init_new_bsp_segment(void);
void			destroy_full_bsp_segment(void *bsp_seg);
t_bsp_segment	*duplicate_bsp_segment(t_bsp_segment *original);

t_list			*create_bsp_segment_node(void);
t_list			*convert_to_bsp_segments(t_list *segment_list);
t_list			*duplicate_bsp_segment_node(t_list *original_node);
void			destroy_full_bsp_segment_node(t_list *node);

int				map_cut(t_list **bsp_segments, t_list **left, t_list **right);

t_vector4d		get_segment_max_on_separator(t_bsp_segment *bsp_segment,
					int use_x);
t_vector4d		get_segment_min_on_separator(t_bsp_segment *bsp_segment,
					int use_x);
void			sort_intersect_segments_array(t_list **bsp_segments_nodes_array,
					int size, int is_sep_horizontal);

int				construct_bsp(t_list **segments, t_tree_node **tree);

void			destroy_segment_tree(t_tree_node **tree);

int				cut_segment(t_bsp_segment *bsp_segment,
					t_bsp_segment **new_segment_right);
int				cut_portal(t_bsp_segment *bsp_segment,
					t_bsp_segment **right_portal_1,
					t_bsp_segment **right_portal_2);

int				cut_segment_to_node(t_list **bsp_segment_node, t_list **left,
					t_list **right);

int				create_portals(t_list *bsp_segments, t_segment_d *separator,
					t_list **portal_lst);

void			bsp_segment_compute_intersec(t_bsp_segment *segment,
					t_segment_d *separator);

int				cut_space(t_list **segments, t_segment_d *separator,
					t_list **left, t_list **right);

// BSP

t_list			*choose_separator(t_list *bsp_segments);

// BSP_SEGMENT_UTILS
// TODO: maybe move in structure.h ?
t_bsp_segment	*create_bsp_segment(t_segment_d *segment);
void			destroy_full_bsp_segment(void *bsp_seg);
t_bsp_segment	*init_new_bsp_segment(void);
t_bsp_segment	*duplicate_bsp_segment(t_bsp_segment *original);

void			destroy_bsp_segment_tree_node(t_tree_node *node);
void			destroy_bsp_segment_tree(t_tree_node **tree);

// Segment utils only used in bsp builder
void			compute_bsp_segments_intersections(t_list *bsp_segments,
					t_segment_d *separator);
void			tree_convert_bsp_segment_to_segments(t_tree_node *tree);
void			tree_update_portals_links_to_segments(t_tree_node *tree);

#endif
