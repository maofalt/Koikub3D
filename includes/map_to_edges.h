/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_edges.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:41:27 by motero            #+#    #+#             */
/*   Updated: 2023/10/08 21:01:48 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_TO_EDGES_H
# define MAP_TO_EDGES_H

# include  "cub3D.h"

/*############################################################################*/
/*                              MAP TO EDGE CONVERSION  DEFINITION            */
/*############################################################################*/

void		exploreEdge(t_edge_exploration_context *context);
int         extractEdgesRecursively(char** map, t_list **edges);
int			add_edge(t_segment_d new_segment, t_list **edges);
t_direction	**malloc2DArray(char **map);

#endif