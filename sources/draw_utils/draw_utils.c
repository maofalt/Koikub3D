/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2023/10/14 20:28:42 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"

void	img_pix_put(t_img_data *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	point_space_partitioning(t_segment_d *separator, t_point2d *point)
{
	t_vector4d	ab;
	t_vector4d	ap;
	t_vector4d	tmp_point;

	tmp_point = point2d_to_vector4d(point);
	ab.vec = separator->point_b.vec - separator->point_a.vec;
	ap.vec = tmp_point.vec - separator->point_a.vec;
	return (ab.x * ap.y - ab.y * ap.x);
}