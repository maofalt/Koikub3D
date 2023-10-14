/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_builder.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:34:36 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/14 06:15:46 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSP_BUILDER_H
# define BSP_BUILDER_H

# include "structures.h"

int			point_space_partitioning(t_segment_d *separator, t_point2d *point);
t_point2d	find_intersection(t_segment_d line, t_segment_d seg);
void		lst_move_node(t_list **list, t_list **node);

// int			construct_bsp(t_list **segments, t_tree_node **tree);
int construct_bsp(t_list **segments, t_tree_node **tree, t_cub *data);

int			cut_space(
				t_list **segments,
				t_segment_d *separator,
				t_list **left,
				t_list **right);

#endif
