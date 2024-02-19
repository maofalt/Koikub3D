/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager_destroy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:31:28 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/19 22:28:55 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ressources_managers.h"
#include "settings.h"
#include "structures.h"

int	texture_manager_destroy(t_cub *data)
{
	int	i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		texture_destroy(data->texture_manager.textures + i);
		++i;
	}
	return (0);
}
