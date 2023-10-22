/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_buffering_canvas.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/16 23:14:09 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

void	copy_canvas_to_temp(t_list *canvas_list)
{
	const t_canvas	*final_canvas = get_canvas_from_list(canvas_list, MAP);
	const t_canvas	*temp_canvas
		= get_canvas_from_list(canvas_list, FINAL_TEMP);
	size_t			size;

	if (final_canvas && temp_canvas
		&& final_canvas->pixels && temp_canvas->pixels)
	{
		size = final_canvas->size.x * final_canvas->size.y * sizeof(t_color);
		ft_memcpy(temp_canvas->pixels, final_canvas->pixels, size);
	}
}

void	copy_temp_to_screen(t_list *canvas_list, t_img_data *img)
{
	const t_canvas	*temp_canvas
		= get_canvas_from_list(canvas_list, FINAL_TEMP);
	t_point2i		pos;
	t_color			color;

	if (!temp_canvas || !temp_canvas->pixels || !img)
		return ;
	pos = (t_point2i){{0, 0}};
	while (pos.y < temp_canvas->size.y)
	{
		while (pos.x < temp_canvas->size.x)
		{
			color = temp_canvas->pixels[pos.y * temp_canvas->size.x + pos.x];
			img_pix_put(img, pos.x, pos.y, (int)color.rgb_color);
			pos.x++;
		}
		pos.y++;
	}
}

void	copy_temp_to_canvas(t_list *canvas_list)
{
	const t_canvas	*final_canvas = get_canvas_from_list(canvas_list, MAP);
	const t_canvas	*temp_canvas
		= get_canvas_from_list(canvas_list, FINAL_TEMP);
	size_t			size;

	if (final_canvas && temp_canvas
		&& final_canvas->pixels && temp_canvas->pixels)
	{
		size = final_canvas->size.x * final_canvas->size.y * sizeof(t_color);
		ft_memcpy(final_canvas->pixels, temp_canvas->pixels, size);
	}
}

t_point2i	screen_to_canvas(t_point2i screen_point, t_canvas *canvas)
{
	t_point2i	canvas_point;

	canvas_point.x = round(screen_point.x * canvas->inv_scale.x);
	canvas_point.y = round(screen_point.y * canvas->inv_scale.y);
	return (canvas_point);
}
