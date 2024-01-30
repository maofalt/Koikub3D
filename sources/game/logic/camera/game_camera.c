/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 23:54:17 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/28 14:17:56 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_loop.h"
#include "maths_utils.h"
#include "settings.h"

static double	_dot_product_3d(t_vector4d *vec1, t_vector4d *vec2)
{
	const t_v4d	product = vec1->vec * vec2->vec;

	return (product[0] + product[1] + product[2]);
}

static void	update_effects(t_game_data *data)
{
	t_camera_effects	*effects;

	effects = &data->state.player_camera.effects;
	effects->wave.enabled = false;
	if (effects->wave.enabled)
	{
		effects->wave.amplitude_x = 2;
		effects->wave.amplitude_y = 5;
		effects->wave.frequency_x = 0.1;
		effects->wave.frequency_y = 0.05;
		effects->wave.offset_x += 0.12;
		effects->wave.offset_y += 0.12;
	}
}

void	game_update_camera(t_game_data *data)
{
	double	tilt;

	data->state.player_camera.dir = data->state.player.dir;
	data->state.player_camera.right = data->state.player.right;
	data->state.player_camera.pos = data->state.player.pos;
	data->state.player_camera.velocity = data->state.player.velocity;
	tilt = _dot_product_3d(&data->state.player_camera.velocity,
			&data->state.player_camera.right);
	data->state.player_camera.tilt = tilt * TILT_FACTOR;
	update_effects(data);
}