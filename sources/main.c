/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:11:18 by motero            #+#    #+#             */
/*   Updated: 2024/02/27 18:47:35 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "game_loop.h"
#include "map_to_edges.h"
#include "bsp_builder.h"
#include "ressources_managers.h"

void	free_everything(t_cub data)
{
	destroy_assets(&data);
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
	if (data.screen.mlx_img)
		mlx_destroy_image(data.mlx_ptr, data.screen.mlx_img);
	if (data.mlx_ptr != NULL)
		mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	if (data.map != NULL)
		free_double_char(data.map);
	game_destroy(&data.game_data);
	ft_lstclear(&data.segments_list, free);
	free_canvas_list(data.canvas_list);
}

static void	free_setup_canvas(t_setup_by_game_state *setup_cavas)
{
	int	i;

	i = 0;
	while (i < END_GAME_STATE)
	{
		free(setup_cavas[i].canvas_configurations);
		i++;
	}
	free(setup_cavas);
}

static int	start_main_loop(t_cub *data, t_setup_by_game_state **setup_cavas)
{
	*setup_cavas = initialize_canvas_setups();
	data->setup_canvas = (void *)*setup_cavas;
	data->canvas_list = initialize_canvas_list(data->game_state, *setup_cavas);
	if (data->canvas_list == NULL)
		return (1);
	data->active_canvas = get_canvas_from_list(data->canvas_list, BUTTON);
	if (mlx_loop_hook(data->mlx_ptr, &render, data))
		ft_mlx_engine(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub					data;
	t_setup_by_game_state	*setup_canvas;

	setup_canvas = NULL;
	if (argc != 2)
		return (printf("Error\nToo many Arguments"), 1);
	ft_memset(&data, 0, sizeof(t_cub));
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	if (initialize_and_preload_assets(&data))
		return (free_everything(data), 1);
	data.update = UPDATE;
	data.game_state = MENU;
	if (!main_parsing(&data, argv[1]) || ft_mlx_initialize_pointers(&data))
		return (free_everything(data), 1);
	if (start_main_loop(&data, &setup_canvas))
		printf("Error\nGame logic failed");
	free_everything(data);
	free_setup_canvas(setup_canvas);
}
