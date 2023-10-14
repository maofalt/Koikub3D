/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/13 23:50:38 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

int	draw_line(t_shape_params *params)
{
	t_line_params		line;

	line = params->shape.line;
	draw_one_line(params->img, &line, params->color);
	return (0);
}

int	draw_rectangle(t_shape_params *params)
{
	const t_rectangle_params	rect = params->shape.rect;
	t_line_params				line;

	line.start = rect.top_left;
	line.end = rect.top_right;
	draw_one_line(params->img, &line, params->color);
	line.start = rect.bottom_left;
	line.end = rect.bottom_right;
	draw_one_line(params->img, &line, params->color);
	line.start = rect.top_left;
	line.end = rect.bottom_left;
	draw_one_line(params->img, &line, params->color);
	line.start = rect.top_right;
	line.end = rect.bottom_right;
	draw_one_line(params->img, &line, params->color);
	return (0);
}

int	draw_triangle(t_shape_params *params)
{
	t_line_params			line;
	const t_triangle_params	triangle = params->shape.triangle;

	line.start = triangle.pt1;
	line.end = triangle.pt2;
	draw_one_line(params->img, &line, params->color);
	line.start = triangle.pt2;
	line.end = triangle.pt3;
	draw_one_line(params->img, &line, params->color);
	line.start = triangle.pt3;
	line.end = triangle.pt1;
	draw_one_line(params->img, &line, params->color);
	return (0);
}

void	draw_circle_points(t_img_data *img,
	t_point2i center,
	t_point2i point,
	t_color color)
{
	img_pix_put(img, center.x + point.x, center.y + point.y,
		(int)color.rgb_color);
	img_pix_put(img, center.x - point.x, center.y + point.y,
		(int)color.rgb_color);
	img_pix_put(img, center.x + point.x, center.y - point.y,
		(int)color.rgb_color);
	img_pix_put(img, center.x - point.x, center.y - point.y,
		(int)color.rgb_color);
	img_pix_put(img, center.x + point.y, center.y + point.x,
		(int)color.rgb_color);
	img_pix_put(img, center.x - point.y, center.y + point.x,
		(int)color.rgb_color);
	img_pix_put(img, center.x + point.y, center.y - point.x,
		(int)color.rgb_color);
	img_pix_put(img, center.x - point.y, center.y - point.x,
		(int)color.rgb_color);
}

int	draw_circle(t_shape_params *params)
{
	const t_circle_params	circle = params->shape.circle;
	const t_point2i			center
		= (t_point2i){{circle.center.x, circle.center.y}};
	t_point2i				coord;
	t_point2i				current_point;

	coord = (t_point2i){{0, circle.radius}};
	current_point = coord;
	int d = 3 - 2 * circle.radius;

	draw_circle_points(params->img, center, current_point, params->color);
	while (coord.y >= coord.x)
	{
		coord.x++;
		if (d > 0)
		{
			coord.y--;
			d = d + 4 * (coord.x - coord.y) + 10;
		}
		else
			d = d + 4 * coord.x + 6;
		current_point.x = coord.x;
		current_point.y = coord.y;
		draw_circle_points(params->img, center, current_point, params->color);
	}
	return (0);
}
