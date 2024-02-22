/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:31:15 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 04:19:02 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"
#include "draw_utils.h"
#include "game_loop.h"
#include "settings.h"

//TODO move this in .h
void	map_destroy(t_map_data *map_data);

void	game_destroy(t_game_data *game_data)
{
	printf("game_destroy\n");
	entities_destroy_all(game_data);
	sparse_array_destroy(game_data->state.entities);
	map_destroy(&game_data->map_data);
	game_render_destroy(game_data);
}
