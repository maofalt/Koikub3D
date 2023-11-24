/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:31:28 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/24 17:52:10 by olimarti         ###   ########.fr       */
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
	if (texture_init(data->texture_manager.textures, 4, 10000))
		return (1);
	texture_set(data->texture_manager.textures, 0, data->texture + 0);
	texture_set(data->texture_manager.textures, 1, data->texture + 1);
	texture_set(data->texture_manager.textures, 2, data->texture + 1);
	texture_set(data->texture_manager.textures, 3, data->texture + 2);
	data->texture_manager.texture_count = 1;
	return (0);
}
