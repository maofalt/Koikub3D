/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:11:18 by motero            #+#    #+#             */
/*   Updated: 2024/02/25 05:14:23 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "game_loop.h"
#include "map_to_edges.h"
#include "bsp_builder.h"
#include "ressources_managers.h"

void	map_destroy(t_map_data *map_data); //TODO remove this


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
	mlx_destroy_image(data.mlx_ptr, data.screen.mlx_img);
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

int	game_logic(t_cub *data, t_setup_by_game_state **setup_cavas)
{
	// if (mlx_loop_hook(data.mlx_ptr, &map_visualizer_render, &data))
	// 	ft_mlx_engine(&data);
	//data->game_state = MAP_EDITOR;
	*setup_cavas = initialize_canvas_setups();
	data->setup_canvas = (void *)*setup_cavas;
	data->canvas_list = initialize_canvas_list(data->game_state, *setup_cavas);
	if (data->canvas_list == NULL)
		return (1);
	// if (game_init(&data))
	// 	return (1);
	data->active_canvas = get_canvas_from_list(data->canvas_list, BUTTON);
	if (mlx_loop_hook(data->mlx_ptr, &render, data))
		ft_mlx_engine(data);
	return (0);
}

void	set_segments_ceil_floor(t_list *seg_lst)
{
	t_segment_d *seg;

	while (seg_lst)
	{
		seg = seg_lst->content;

		seg->data.ceil = -3;
		seg->data.floor = 1;
		seg_lst = seg_lst->next;
	}
}


void	tmp_set_segments_textures(t_list *lst, t_cub *data)
{
	t_segment_d *seg;

	while (lst)
	{
		seg = lst->content;
		seg->data.data.wall.texture.texture = data->texture_manager.textures;
		seg->data.data.wall.texture.offset = 0;
		lst = lst->next;
	}

}

static void	lst_update_portals_textures(
	t_list **bsp_list,
	t_texture_ptr *padding_texture_top,
	t_texture_ptr *padding_texture_bottom
	)
{
	t_list			*current;
	t_segment_d	*seg;

	current = *bsp_list;
	while (current != NULL)
	{
		seg = (t_segment_d *)current->content;
		if (seg->data.type == PORTAL)
		{
			seg->data.data.portal.padding_texture_bottom
				= *padding_texture_bottom;
			seg->data.data.portal.padding_texture_top = *padding_texture_top;
			seg->data.data.portal.dijkstra_id = -1;
		}
		current = current->next;
	}
}

void	tree_update_update_portals_textures(
	t_tree_node *tree,
	t_texture_ptr *padding_texture_top,
	t_texture_ptr *padding_texture_bottom
	)
{
	if (tree->left == NULL && tree->right == NULL)
	{
		lst_update_portals_textures(
			&((t_bsp_tree_node_data*)tree->data)->sector_segments,
			padding_texture_top, padding_texture_bottom);
		return ;
	}
	tree_update_update_portals_textures(tree->left,
		padding_texture_top, padding_texture_bottom);
	tree_update_update_portals_textures(tree->right,
		padding_texture_top, padding_texture_bottom);
}


void set_bsp_default_textures(t_cub *data)
{
	t_texture_ptr texture_ptr;

	texture_ptr.texture = data->texture_manager.textures;
	printf("hello: %i\n", texture_ptr.texture->frame_count);
	texture_ptr.offset = 0;
	tree_update_update_portals_textures(data->game_data.map_data.bsp,
	&texture_ptr, &texture_ptr);
}

//TODO: move it
int	map_convert(t_cub *data, t_map_data *map_data)
{
	t_list		**segments_lst;
	t_tree_node	*tree;

	tree = NULL;
	segments_lst = &data->segments_list;
	if (!*segments_lst && extract_edge_recursively(data->map, segments_lst))
		return (1);
	set_segments_ceil_floor(*segments_lst);
	tmp_set_segments_textures(*segments_lst, data);
	if (construct_bsp(segments_lst, &tree))
	{
		ft_lstclear(segments_lst, free);
		return (1);
	}
	map_data->segments = *segments_lst;
	map_data->bsp = tree;
	set_bsp_default_textures(data);
	return (0);
}

//TODO: move it
void	map_destroy(t_map_data *map_data)
{
	destroy_segment_tree(&map_data->bsp);
}

int	main(int argc, char **argv)
{
	t_cub					data;
	t_setup_by_game_state	*setup_canvas;

	setup_canvas = NULL;
	if (argc != 2)
		return (printf("Error\nToo many Arguments"), 1);
	ft_memset(&data, 0, sizeof(t_cub));
	ft_mlx_initialize_pointers(&data);
	if (data.mlx_ptr == NULL)
		return (1);
	if (initialize_and_preload_assets(&data))
		return (free_everything(data), 1);
	data.update = UPDATE;
	data.game_state = MENU;
	if (!main_parsing(&data, argv[1]))
		return (free_everything(data), 1);
	if (game_logic(&data, &setup_canvas))
		printf("Error\nGame logic failed");
	free_everything(data);
	free_setup_canvas(setup_canvas);
}
