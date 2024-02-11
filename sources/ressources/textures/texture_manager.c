/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:31:28 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/11 07:49:44 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ressources_managers.h"
#include "settings.h"
#include "structures.h"


typedef struct s_texture_asset_params
{
	t_texture_id		texture_id;
	t_game_assets		*game_images;
	int					ms_per_frame;
	int					frame_count;
}	t_texture_asset_params;

t_game_assets	g_duck_idle_images[] = {
	DUCK_TEXTURE_IDLE_00,
	DUCK_TEXTURE_IDLE_01
};

t_game_assets	g_duck_walk_images[] = {
	DUCK_TEXTURE_WALK_00,
	DUCK_TEXTURE_WALK_01,
	DUCK_TEXTURE_WALK_02,
	DUCK_TEXTURE_WALK_03
};

t_texture_asset_params	g_texture_asset_loader[] = {
{
	TEXTURE_DUCK_IDLE,
	g_duck_idle_images,
	100,
	sizeof(g_duck_idle_images) / sizeof(g_duck_idle_images[0]),
},
{
	TEXTURE_DUCK_WALK,
	g_duck_walk_images,
	100,
	sizeof(g_duck_walk_images) / sizeof(g_duck_walk_images[0]),
},
};


//TODO: add delta time;
void	texture_manager_update(t_texture_manager *texture_manager)
{
	int	i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		texture_update(texture_manager->textures + i, 16);
		++i;
	}
}

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

int	load_assets_textures(t_cub *data)
{
	const int	texture_count
		= sizeof(g_texture_asset_loader) / sizeof(t_texture_asset_params);
	int			i;
	int			j;
	int			current_texture;

	i = 0;
	while (i < texture_count)
	{
		if (texture_init(data->texture_manager.textures
				+ g_texture_asset_loader[i].texture_id,
				g_texture_asset_loader[i].frame_count,
				g_texture_asset_loader[i].ms_per_frame))
			return (1);
		current_texture = g_texture_asset_loader[i].texture_id;
		j = 0;
		while (j < g_texture_asset_loader[i].frame_count)
		{
			texture_set(data->texture_manager.textures + current_texture, j,
				&data->game_images[g_texture_asset_loader[i].game_images[j]]);
			++j;
		}
		++i;
	}
	return (0);
}

int	check_all_textures_loaded(t_cub *data)
{
	int		i;
	bool	error;

	i = 0;
	error = 0;
	while (i < TEXTURE_COUNT)
	{
		if (data->texture_manager.textures[i].frames == NULL)
		{
			printf("Error texture %d not loaded\n", i);
			error |= 1;
		}
		++i;
	}
	return (error);
}

int	texture_manager_init(t_cub *data)
{
	t_texture_manager *const	texture_manager = &data->texture_manager;

	ft_memset(texture_manager, 0, sizeof(data->texture_manager));
	if (!texture_init(texture_manager->textures + TEXTURE_WALL_NORTH, 1, 1000))
		texture_set(texture_manager->textures, 0,
			data->texture + TEXTURE_WALL_NORTH);
	if (!texture_init(texture_manager->textures + TEXTURE_WALL_SOUTH, 1, 1000))
		texture_set(texture_manager->textures + TEXTURE_WALL_SOUTH, 0,
			data->texture + TEXTURE_WALL_SOUTH);
	if (!texture_init(texture_manager->textures + TEXTURE_WALL_EAST, 1, 1000))
		texture_set(texture_manager->textures + TEXTURE_WALL_EAST, 0,
			data->texture + TEXTURE_WALL_EAST);
	if (!texture_init(texture_manager->textures + TEXTURE_WALL_WEST, 1, 1000))
		texture_set(texture_manager->textures + TEXTURE_WALL_WEST, 0,
			data->texture + TEXTURE_WALL_WEST);
	load_assets_textures(data);
	if (check_all_textures_loaded(data))
	{
		texture_manager_destroy(data);
		return (1);
	}
	return (0);
}
