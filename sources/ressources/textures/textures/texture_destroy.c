/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:23:11 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/19 22:25:02 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "maths_utils.h"
#include "structures.h"
#include <assert.h>

void	texture_destroy(t_texture *texture)
{
	if (texture)
	{
		free(texture->frames);
		texture->frames = NULL;
	}
}
