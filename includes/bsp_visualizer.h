/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_visualizer.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:55:23 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/11 01:37:57 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSP_VISUALIZER_H
# define BSP_VISUALIZER_H

# include "structures.h"
# include "draw_utils.h"

/*############################################################################*/
/*                                MAP DISPLAY                                 */
/*############################################################################*/
int		map_visualizer_render(t_cub *data);

/*############################################################################*/
/*                                MAP CONVERSION                              */
/*############################################################################*/

int		convert_map_to_segments(t_cub *data, t_list **segment_lst);
int		add_segment_to_lst(t_list **lst, t_segment_d segment);
t_list	*create_initialized_segment_node(t_segment_d segment);
t_list	*create_segment_node(void);



#endif
