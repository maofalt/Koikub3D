/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displacement_tilt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:12:13 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/28 01:12:38 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_utils.h"
#include "structures.h"
#include <math.h>

t_point2i	displacement_tilt(t_point2i old_pos, t_3d_render *render)
{
	t_point2i	new_pos;
	t_point2i	pos;
	double		rotation_x;
	double		rotation_y;

	pos = (t_point2i){{old_pos.x - render->middle.x, old_pos.y
		- render->middle.y}};
	rotation_x = render->camera->tilt;
	rotation_y = render->camera->tilt;
	new_pos.x = pos.x * cos(rotation_x) - pos.y * sin(rotation_x)
		+ render->middle.x;
	new_pos.y = pos.x * sin(rotation_y) + pos.y * cos(rotation_y)
		+ render->middle.y;
	return (new_pos);
}
