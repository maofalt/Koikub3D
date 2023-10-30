/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:11:18 by motero            #+#    #+#             */
/*   Updated: 2023/10/29 18:44:11 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "game_loop.h"
#include "map_to_edges.h"
#include "bsp_builder.h"


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
	//TODO: destroy bsp
}

//TODO: move it
int	map_convert(t_cub *data)
{
	t_list		*segments_lst;
	t_tree_node	*tree;

	tree = NULL;
	segments_lst = NULL;
	if (extract_edge_recursively(data->map, &segments_lst))
		return (1);
	// if (construct_bsp(&segments_lst,(t_list **)&(t_list* ){NULL},  &tree))
	// {
	// 	//TODO: free segments
	// 	return (1);
	// }
	data->map_data.segments = NULL;
	data->map_data.bsp = tree;
	// if (extract_edge_recursively(data->map, &data->map_data.segments))
	// 	return (1); //TODO free and bsp
	return (0);
}

void	map_destroy(t_cub *data)
{
	//TODO destruct_bsp
	(void)data;
}

int	main(int argc, char **argv)
{
	t_cub	data;

	(void)argv;
	if (argc != 2)
		return (printf("Error\nToo many Arguments"), 1);
	ft_memset(&data, 0, sizeof(t_cub));
	ft_mlx_initialize_pointers(&data);
	if (data.mlx_ptr == NULL)
		return (1);
	data.update = 1;
	if (!main_parsing(&data, argv[1]))
	{
		return (free_everything(data), 1);
	}
	// if (mlx_loop_hook(data.mlx_ptr, &map_visualizer_render, &data))
	// 	ft_mlx_engine(&data);
	data.canvas_list = NULL;
	data.canvas_list = initialize_canvas_list(
			(t_point2i){{WINDOW_WIDTH, WINDOW_HEIGHT}},
			(t_point2i){{WINDOW_WIDTH * 0.8, WINDOW_HEIGHT / 3}},
			(t_point2i){{WINDOW_WIDTH, WINDOW_HEIGHT}});
	if (data.canvas_list == NULL)
		return (free_everything(data), 1);
	if (map_convert(&data))
		return (free_everything(data), 1);
	mlx_loop_hook(data.mlx_ptr, &game_loop, &data);
	ft_mlx_engine(&data);
	free_everything(data);
}
