/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 23:54:17 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/23 17:48:13 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_loop.h"
#include "maths_utils.h"
#include "settings.h"

static double _dot_product_3d(t_vector4d *vec1, t_vector4d *vec2)
{
	const t_v4d	product = vec1->vec * vec2->vec;

	return (product[0] + product[1] + product[2]);
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
	data->state.player_camera.tilt = tilt; //* TILT_FACTOR;
}
