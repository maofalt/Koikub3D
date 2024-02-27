/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 02:12:13 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 02:12:43 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "draw_utils.h"
# include "render_3D.h"
# include "structures.h"

double		dot_product_2d(
				const t_vector4d *const vec1,
				const t_vector4d *const vec2);
t_point2d	find_intersection_points(
				t_vector4d const line_point_a,
				t_vector4d const line_point_b,
				t_vector4d const seg_a,
				t_vector4d const seg_b);
double		point_space_partitioning_v4d(
				t_segment_d *separator,
				t_vector4d *point);
t_tree_node	*bsp_search_point_fast(
				t_tree_node *tree,
				t_vector4d *point);

#endif
