/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:31:28 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/30 23:03:56 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ressources_managers.h"


void	texture_manager_update(t_texture_manager *texture_manager)
{
	int	i;

	i = 0;
	while (i < texture_manager->texture_count)
	{
		texture_update(texture_manager->textures + i, 16);
		//add delta time;
		++i;
	}
}

int	texture_manager_destroy(t_cub *data)
{
	texture_destroy(data->texture_manager.textures + 0);
	texture_destroy(data->texture_manager.textures);
	return (0);
}

int	texture_manager_init(t_cub *data)
{
	// if (texture_init(data->texture_manager.textures, 4, 1000))
	// 	return (1);
	// texture_set(data->texture_manager.textures, 0, data->texture + 0);
	// texture_set(data->texture_manager.textures, 1, data->texture + 1);
	// texture_set(data->texture_manager.textures, 2, data->texture + 1);
	// texture_set(data->texture_manager.textures, 3, data->texture + 2);
	// data->texture_manager.texture_count = 1;

	if (texture_init(data->texture_manager.textures, 4, 1000))
		return (1);
	texture_set(data->texture_manager.textures, 0, data->texture + 0);
	texture_set(data->texture_manager.textures, 1, data->texture + 1);
	texture_set(data->texture_manager.textures, 2, data->texture + 2);
	texture_set(data->texture_manager.textures, 3, data->texture + 3);

	if (texture_init(data->texture_manager.textures +1, 4, 1000))
		return (1);
	texture_set(data->texture_manager.textures + 1, 0, data->texture + 1);
	texture_set(data->texture_manager.textures + 1, 1, data->texture + 2);
	texture_set(data->texture_manager.textures + 1, 2, data->texture + 3);
	texture_set(data->texture_manager.textures + 1, 3, data->texture + 0);

	if (texture_init(data->texture_manager.textures +2, 4, 1000))
		return (1);

	texture_set(data->texture_manager.textures + 2, 0, data->texture + 2);
	texture_set(data->texture_manager.textures + 2, 1, data->texture + 3);
	texture_set(data->texture_manager.textures + 2, 2, data->texture + 0);
	texture_set(data->texture_manager.textures + 2, 3, data->texture + 1);

	if (texture_init(data->texture_manager.textures + 3, 4, 1000))
		return (1);

	texture_set(data->texture_manager.textures + 3, 0, data->texture + 3);
	texture_set(data->texture_manager.textures + 3, 1, data->texture + 0);
	texture_set(data->texture_manager.textures + 3, 2, data->texture + 1);
	texture_set(data->texture_manager.textures + 3, 3, data->texture + 2);

	data->texture_manager.texture_count = 4;
	return (0);
}
