/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 04:12:47 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/16 17:45:38 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"

void	player_handle_event(t_cub *data)
{
	data->player.pos.y -= data->inputs.action_states[a_move_up];
	data->player.pos.y += data->inputs.action_states[a_move_down];
	data->player.pos.x -= data->inputs.action_states[a_move_left];
	data->player.pos.x += data->inputs.action_states[a_move_right];
}
