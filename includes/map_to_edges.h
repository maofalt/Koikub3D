/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_edges.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:41:27 by motero            #+#    #+#             */
/*   Updated: 2023/10/08 18:53:07 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "cub3d.h"

/*############################################################################*/
/*                              MAP TO EDGE CONVERSION  DEFINITION            */
/*############################################################################*/

void    exploreEdge(t_edge_exploration_context *context);

int     extractEdgesRecursively(char** map);

int     addEdge(t_segment_d new_segment, t_list **edges);