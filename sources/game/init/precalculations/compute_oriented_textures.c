/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_oriented_textures.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 22:21:30 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/30 22:56:10 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include <math.h>
#include <stdio.h>

static int	calc_vector_sector(t_vector4d *vec, int sector_count)
{
	double	angle;

	angle = atan2(vec->y, vec->x);
	if (angle < 0)
		angle += M_PI * 2;

	return (sector_count * angle / (2 * M_PI));
}


// Note: Make sure to calculate the normal before calling this function
void	compute_oriented_textures(
	__attribute_maybe_unused__ t_game_data *game_data,
	t_segment_d *segment,
	t_bsp_tree_node_data *sector)
{
	int	vector_sector;
	int	sector_count;

	sector_count = game_data->map_data.texture_manager->texture_count;
	sector_count = fmin(sector_count, 4);
	vector_sector = calc_vector_sector(&segment->data.normal,
			game_data->map_data.texture_manager->texture_count);

	printf("vector_count: %d\n", game_data->map_data.texture_manager->texture_count);
	printf("sector_count: %d\n", sector_count);
	printf("texture_count: %d\n", game_data->map_data.texture_manager->texture_count);
	printf("sector: %p\n", (void*)sector);


	if (segment->data.type == WALL)
	{
		segment->data.data.wall.texture.texture
			= &game_data->map_data.texture_manager->textures[vector_sector];
	}
	else
	{
		segment->data.data.portal.padding_texture_bottom.texture
			= &game_data->map_data.texture_manager->textures[vector_sector];
		segment->data.data.portal.padding_texture_bottom.texture
			= &game_data->map_data.texture_manager->textures[vector_sector];
	}
}
