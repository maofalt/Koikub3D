/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_sector_floor_ceiling.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 00:38:03 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/25 01:32:46 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "maths_utils.h"

double	_random_ceil(void)
{
	static unsigned int	seed = 0;

	seed = seed * 1103515245 + 12345;
	return ((double)(seed & 0x7fffffff) / 0x7fffffff);
}

void	compute_sector_floor_ceiling(
	__attribute_maybe_unused__ t_game_data *game_data,
	t_bsp_tree_node_data *sector)
{
	double		ceil;
	double		floor;
	double		dist;

	ceil = DEFAULT_CEIL_HEIGHT;
	floor = DEFAULT_FLOOR_HEIGHT;
	dist = _random_ceil();
	sector->sector_data.ceil = ceil * dist;
	sector->sector_data.floor = floor;
}
