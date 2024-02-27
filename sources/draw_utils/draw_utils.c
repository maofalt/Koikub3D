/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2024/02/27 00:20:33 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"

void	img_pix_put(t_img_data *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	put_pixel_transparent(t_color *dest, t_color *src)
{
	double	alpha;

	if (src->a == 255)
		return (255);
	if (src->a == 0)
	{
		dest->d = src->d;
		return (0);
	}
	alpha = (double)src->a / 255.0;
	dest->r = (1 - alpha) * (double)src->r + alpha * (double)dest->r;
	dest->g = (1 - alpha) * (double)src->g + alpha * (double)dest->g;
	dest->b = (1 - alpha) * (double)src->b + alpha * (double)dest->b;
	dest->a = 255;
	return (src->a);
}
