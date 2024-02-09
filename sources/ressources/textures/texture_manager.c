/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:31:28 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/09 08:38:43 by olimarti         ###   ########.fr       */
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
	//TODO : add error handling
	data->texture_manager.texture_count = 0;
	if (texture_init(data->texture_manager.textures, 1, 1000))
		return (1);
	texture_set(data->texture_manager.textures, 0, data->texture + 0);
	if (texture_init(data->texture_manager.textures + 1, 1, 1000))
		return (1);
	texture_set(data->texture_manager.textures + 1, 0, data->texture + 1);
	if (texture_init(data->texture_manager.textures + 2, 1, 1000))
		return (1);
	texture_set(data->texture_manager.textures + 2, 0, data->texture + 2);
	if (texture_init(data->texture_manager.textures + 3, 1, 1000))
		return (1);
	texture_set(data->texture_manager.textures + 3, 0, data->texture + 3);
	if (texture_init(data->texture_manager.textures + 4, 4, 100))
		return (1);
	texture_set(data->texture_manager.textures + 4, 0,
		&data->game_images[DUCK_TEXTURE_WALK_00]);
	texture_set(data->texture_manager.textures + 4, 1,
		&data->game_images[DUCK_TEXTURE_WALK_01]);
	texture_set(data->texture_manager.textures + 4, 2,
		&data->game_images[DUCK_TEXTURE_WALK_02]);
	texture_set(data->texture_manager.textures + 4, 3,
		&data->game_images[DUCK_TEXTURE_WALK_03]);
	if (texture_init(data->texture_manager.textures + 5, 2, 100))
		return (1);
	texture_set(data->texture_manager.textures + 5, 0,
		&data->game_images[DUCK_TEXTURE_IDLE_00]);
	texture_set(data->texture_manager.textures + 5, 1,
		&data->game_images[DUCK_TEXTURE_IDLE_01]);
	// if (texture_init(data->texture_manager.textures + 6, 1, 1000))
	// 	return (1);
	// texture_set(data->texture_manager.textures + 6, 0,
	// 	&data->game_images[MONSTER_LINE_TEXTURE]);
	data->texture_manager.texture_count = 6;

	return (0);
}
