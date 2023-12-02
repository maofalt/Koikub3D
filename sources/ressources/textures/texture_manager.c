/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:31:28 by olimarti          #+#    #+#             */
/*   Updated: 2023/12/03 00:07:52 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ressources_managers.h"
#include "mlx.h"


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

int	load_bad_apple_xpm(t_cub *data)
{
	int		i;
	int		width;
	int		height;
	t_img_data	*texture = malloc(sizeof(t_img_data) * 2190);

	i = 0;
	width = 0;
	height = 0;
	char *path = NULL;
	if (texture_init(data->texture_manager.textures, 2190, 100))
		return (1);
	while (i < 2190)
	{
		free(path);
		path = ft_strjoin("./textures/bad_apple_xpm/output_frame_", \
		ft_strjoin(ft_itoa(i), ".xpm"));

		texture[i].mlx_img = \
		mlx_xpm_file_to_image(data->mlx_ptr, path, &width, &height);
		if (!texture[i].mlx_img)
		{
			texture[i].mlx_img = NULL;
			printf("Error: %s\n", path);
			perror("eee");
			exit(1);
			return (0);
		}
		texture[i].size = (t_point2i){{width, height}};
		texture[i].addr = mlx_get_data_addr(texture[i].mlx_img, \
		&texture[i].bpp, &texture[i].line_len, \
		&texture[i].endian);
		texture_set(data->texture_manager.textures, i, texture + i);
		++i;
	}
	// *result = texture;
	return (1);
}

int	texture_manager_init(t_cub *data)
{
	load_bad_apple_xpm(data);
	// if (texture_init(data->texture_manager.textures, 4, 10000))
	// 	return (1);
	// texture_set(data->texture_manager.textures, 0, data->texture + 0);
	// texture_set(data->texture_manager.textures, 1, data->texture + 1);
	// texture_set(data->texture_manager.textures, 2, data->texture + 1);
	// texture_set(data->texture_manager.textures, 3, data->texture + 2);
	data->texture_manager.texture_count = 1;
	return (0);
}
