/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:11:18 by motero            #+#    #+#             */
/*   Updated: 2023/10/16 19:54:07 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_everything(t_cub data)
{
	if (data.win_ptr != NULL)
		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	data.win_ptr = NULL;
	if (data.texture[0].mlx_img != NULL)
		mlx_destroy_image(data.mlx_ptr, data.texture[0].mlx_img);
	if (data.texture[1].mlx_img != NULL)
		mlx_destroy_image(data.mlx_ptr, data.texture[1].mlx_img);
	if (data.texture[2].mlx_img != NULL)
		mlx_destroy_image(data.mlx_ptr, data.texture[2].mlx_img);
	if (data.texture[3].mlx_img != NULL)
		mlx_destroy_image(data.mlx_ptr, data.texture[3].mlx_img);
	mlx_destroy_image(data.mlx_ptr, data.screen.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	if (data.map != NULL)
		free_double_char(data.map);
	free_canvas_list(data.canvas_list);
}

int	main(int argc, char **argv)
{
	t_cub					data;
	t_setup_by_game_state	*setup_cavas;

	setup_cavas = NULL;
	if (argc != 2)
		return (printf("Error\nToo many Arguments"), 1);
	ft_memset(&data, 0, sizeof(t_cub));
	ft_mlx_initialize_pointers(&data);
	if (data.mlx_ptr == NULL)
		return (1);
	data.update = NO_UPDATE;
	if (!main_parsing(&data, argv[1]))
		return (free_everything(data), 1);
	// if (mlx_loop_hook(data.mlx_ptr, &map_visualizer_render, &data))
	// 	ft_mlx_engine(&data);
	data.canvas_list = NULL;
	//data.game_state = MAP_EDITOR;
	data.game_state = MENU;
	setup_cavas = initialize_canvas_setups();
	data.canvas_list = initialize_canvas_list(data.game_state, setup_cavas);
	if (data.canvas_list == NULL)
		return (free_everything(data), 1);
	if (mlx_loop_hook(data.mlx_ptr, &map_visualizer_draw, &data))
		ft_mlx_engine(&data);
	free_everything(data);
}
