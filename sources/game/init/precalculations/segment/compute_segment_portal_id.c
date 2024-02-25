/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_segment_portal_id.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:20:11 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/25 05:14:23 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"

void	compute_segment_portal_id(
		__attribute_maybe_unused__ t_game_data *game_data,
		t_segment_d *segment
	)
{
	int	id;

	if (segment->data.type == PORTAL
		&& segment->data.data.portal.dijkstra_id < 0)
	{
		id = game_data->map_data.portal_count
			+ game_data->map_data.sector_count;
		segment->data.data.portal.dijkstra_id = id;
		((t_segment_d *)segment->data.data.portal.destination)
			->data.data.portal.dijkstra_id = id;
		game_data->map_data.portal_count++;
	}
}
