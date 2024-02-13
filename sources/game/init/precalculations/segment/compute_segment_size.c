/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_segment_size.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:20:11 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/29 21:35:03 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"

static double	calc_segment_size(t_segment_d *segment)
{
	return (sqrt(pow(segment->point_b.x - segment->point_a.x, 2)
			+ pow(segment->point_b.y - segment->point_a.y, 2)));
}

void	compute_segment_size(
	__attribute_maybe_unused__ t_game_data *game_data,
	t_segment_d *segment
	)
{
	segment->data.size = calc_segment_size(segment);
}
