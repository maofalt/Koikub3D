/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:53:46 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/06 17:42:02 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_UTILS_H
# define DRAW_UTILS_H

# include "mlx.h"
# include "structures.h"

/*############################################################################*/
/*                              DRAW FUNCTIONS                                */
/*############################################################################*/

void	rectangle(t_img_data *img, t_vector_i pos, t_vector_i size, int color);
void	img_pix_put(t_img_data *img, int x, int y, int color);
void	draw_segment(t_img_data *img, t_segment_d segment, int color);

#endif
