/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 04:12:47 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/19 04:26:37 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "matrix.h"
#include "draw_utils.h"

void player_handle_event(t_cub *data)
{
	t_point2d translation;
	t_point2d forward;
	t_point2d right;
	t_matrix3x3 transformation;
	t_point2d new_translation;
	double angle_movement;

	// Get the movement directions (still in world coordinates)
	translation.x = data->inputs.action_states[a_move_right] - data->inputs.action_states[a_move_left];
	translation.y = data->inputs.action_states[a_move_up] - data->inputs.action_states[a_move_down];
	translation.vec *= 0.2;
	// Get forward and right vectors from player's dir (assuming it's normalized)
	forward = vector4d_to_point2d(&data->player.dir);

	// Compute the right vector (perpendicular) from the forward vector
	right.x = -forward.y;
	right.y = forward.x;

	// Convert world coordinates translation to player's local coordinates
	new_translation.x = translation.x * right.x + translation.y * forward.x;
	new_translation.y = translation.x * right.y + translation.y * forward.y;
	translation = new_translation;

	// Apply the translation to the player's position
	transformation = translation_matrix(translation);
	translation = matrix_vector_multiply(transformation, vector4d_to_point2d(&data->player.pos));
	data->player.pos = point2d_to_vector4d(&translation);

	// Handle the turning of the player
	angle_movement = 0.1 * (data->inputs.action_states[a_turn_right] - data->inputs.action_states[a_turn_left]);
	transformation = rotation_matrix(angle_movement);
	t_point2d rotated_dir = matrix_vector_multiply(transformation, vector4d_to_point2d(&data->player.dir));
	data->player.dir = point2d_to_vector4d(&rotated_dir);
}

