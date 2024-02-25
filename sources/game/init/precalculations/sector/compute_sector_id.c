/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_sector_id.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 00:29:23 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/25 05:15:07 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "maths_utils.h"

void	compute_sector_id(
	t_bsp_tree_node_data *sector,
	t_game_data *game_data)
{
	sector->sector_data.dijkstra_id = game_data->map_data.sector_count
		+ game_data->map_data.portal_count;
	game_data->map_data.sector_count++;
}
