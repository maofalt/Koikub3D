/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_edges.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:41:27 by motero            #+#    #+#             */
/*   Updated: 2023/10/10 16:50:50 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_TO_EDGES_H
# define MAP_TO_EDGES_H

# include  "cub3D.h"

/*############################################################################*/
/*                              MAP TO EDGE CONVERSION  DEFINITION            */
/*############################################################################*/

void		explore_edge(t_edge_exploration_context *context);
int			extract_edge_recursively(char **map, t_list **edges);
int			process_map(t_edge_exploration_context *context, t_list **edges,
				int height_map, int width_map);
int			process_row_vertical_horizontal(t_edge_exploration_context *context, t_list **edges,
				int y, int width_map);
int			process_row_diagonal(t_edge_exploration_context *context, t_list **edges,
				int y, int width_map);		
void		update_context(t_edge_exploration_context *context, t_point2d coord,
				t_point2d delta, t_direction dir);
int			process_direction(t_edge_exploration_context *context,
				t_list **edges, t_point2d delta, t_direction dir);
int			add_edge(t_segment_d new_segment, t_list **edges);
t_direction	**malloc2DArray(char **map);

/*############################################################################*/
/*                       IDENTIFY DIAGONALS ITS HARD                          */
/*############################################################################*/

bool		check_diagonal_left(t_edge_exploration_context *context, t_point2d *coord);
bool		check_if_diagonal_left_splits_vertical_wall(t_edge_exploration_context *context,
				t_point2d *coord);
bool		check_if_diagonal_left_splits_horizontal_wall(t_edge_exploration_context *context,
				t_point2d *coord);
bool		check_diagonal_right(t_edge_exploration_context *context, t_point2d *coord);
#endif