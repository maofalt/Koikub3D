
#include "game_loop.h"


#include "maths_utils.h"


//TODO move this in .h
static t_tree_node	*bsp_search_point(t_tree_node	*tree, t_point2d point)
{
	t_tree_node	*child;
	t_segment_d	separator;
	double		point_side;

	if (!tree)
		return (NULL);
	if (!tree->left || !tree->right)
		return (tree);
	separator = ((t_bsp_tree_node_data *)tree->data)->separator;
	point_side = point_space_partitioning(&separator, &point);
	if (point_side > 0)
		child = bsp_search_point(tree->right, point);
	else
		child = bsp_search_point(tree->left, point);
	if (child != NULL)
		return (child);
	return (NULL);
}


void	update_player_sector_ceil(t_3d_render *render, double value)
{
	t_tree_node				*node;
	t_list					*seg_lst;
	t_segment_d				*segment;

	node = bsp_search_point(render->map->bsp,
			vector4d_to_point2d(&render->camera->pos));

	seg_lst = ((t_bsp_tree_node_data *)node->data)->sector_segments;
	while (seg_lst)
	{
		segment = seg_lst->content;
		segment->data.ceil -= value;
		seg_lst = seg_lst->next;
	}
}

void	update_player_sector_floor(t_3d_render *render, double value)
{
	t_tree_node				*node;
	t_list					*seg_lst;
	t_segment_d				*segment;

	node = bsp_search_point(render->map->bsp,
			vector4d_to_point2d(&render->camera->pos));

	seg_lst = ((t_bsp_tree_node_data *)node->data)->sector_segments;
	while (seg_lst)
	{
		segment = seg_lst->content;
		segment->data.floor += value;
		seg_lst = seg_lst->next;
	}
}


void	sector_edit_handle_event(t_cub *data)
{
	if (data->inputs.action_states[a_decrease_sector_ceil])
	{
		printf("decrease \n");
		update_player_sector_ceil(&data->game_data.game_view_render, -1);
	}
	if (data->inputs.action_states[a_increase_sector_ceil])
	{
		update_player_sector_ceil(&data->game_data.game_view_render, 1);
		printf("increase \n");
	}
	if (data->inputs.action_states[a_decrease_sector_floor])
	{
		printf("decrease \n");

		data->player.pos.z -= 0.1;
		// data->game_data.state.player_camera.pos.z -= 1;
		// update_player_sector_floor(&data->game_data.game_view_render, -1);
	}
	if (data->inputs.action_states[a_increase_sector_floor])
	{
		data->player.pos.z += 0.1;
		// data->game_data.state.player_camera.pos.z += 1;
		// update_player_sector_floor(&data->game_data.game_view_render, 1);
		printf("increase \n");
	}
}

void	update_lights(t_3d_render *render)
{
	t_light			*light;
	int				i;
	static double	frame = 0;

	frame += 0.1;
	i = render->lights_data.light_count;
	while (i--)
	{
		light = &render->lights_data.lights[i];
		if (light->type == DIRECTIONAL_LIGHT)
		{
			light->dir.x = cos(frame); //TODO remove this
			light->dir.y = sin(frame);
		}
	}

}

void	game_update(t_cub *data)
{
	player_handle_event(data);
	sector_edit_handle_event(data);
	update_lights(&data->game_data.game_view_render);
}

int	game_loop(void *self, t_cub *data)
{
	(void)self;
	if (data->win_ptr == NULL)
		return (1);
	game_update(data);
	game_render(data);
	count_fps();
	// usleep(16000);
	data->update = UPDATE;
	return (0);
}
