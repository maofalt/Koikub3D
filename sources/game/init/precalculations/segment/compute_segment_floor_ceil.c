/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_segment_floor_ceil.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:20:11 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/12 00:50:53 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"


void	compute_segment_floor_ceil(
	__attribute_maybe_unused__ t_game_data *game_data,
	t_segment_d *segment,
	t_bsp_tree_node_data *sector)
{
	segment->data.floor = sector->sector_data.floor;
	segment->data.ceil = sector->sector_data.ceil;
}
