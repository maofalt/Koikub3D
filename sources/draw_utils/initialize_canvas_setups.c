/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/13 23:50:38 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

const t_canvas_init_entry g_canvas_init_table[] = 
{
	[0] = {
		.size = (t_point2i){{MAP_CANVAS_SIZE_X, MAP_CANVAS_SIZE_Y}},
		.type = MAP,
		.z_index = MAP_Z_INDEX, .position = (t_point2i){{0, 0}}, .stack = false
	},
	[1] = {
		.size = (t_point2i){{UI_CANVAS_SIZE_X, UI_CANVAS_SIZE_Y}}, .type = UI,
		.z_index = UI_Z_INDEX, .position = (t_point2i){{0, 0}}, .stack = false
	},
	[2] = {
		.size = (t_point2i){{MAP_CANVAS_SIZE_X - UI_CANVAS_SIZE_X, 100}}, .type = UI,
		.z_index = UI_Z_INDEX + 1, .position = (t_point2i){{UI_CANVAS_SIZE_X, 800}}, .stack = false
	},
	[3] = {
		.size = (t_point2i){{FIN_CANVAS_SIZE_X, FIN_CANVAS_SIZE_Y}},
		.type = FINAL,
		.z_index = -2, .position = (t_point2i){{0, 0}}
	},
	[4] = {
		.size = (t_point2i){{MAP_CANVAS_SIZE_X, MAP_CANVAS_SIZE_Y}},
		.type = FIN_TEMP, .z_index = -2,
		.position = (t_point2i){{0, 0}}
	},
	[5] = {
		.type = END_MARKER, .z_index = -99
	}
};



t_setup_by_game_state	*initialize_canvas_setups(void)
{
	t_setup_by_game_state	*canvas_setups;
	const int				nbr_of_game_states = END_GAME_STATE;
	int						i;

	canvas_setups = ft_calloc(nbr_of_game_states,
			sizeof(t_setup_by_game_state));
	if (!canvas_setups)
		return (NULL);
	i = 0;
	while (i < nbr_of_game_states)
	{
		initialize_setup_by_state(&canvas_setups[i], i);
		i++;
	}	
	return (canvas_setups);
}

int	initialize_setup_by_state(t_setup_by_game_state *setup, t_modus_state state)
{
	int	ret;

	setup->game_state = state;
	ret = 0;
	if (state == MAP_EDITOR)
		ret = initialize_map_editor_setup(setup);
	else if (state == GAMEPLAY)
		ret = initialize_gameplay_setup(setup);
	else if (state == MENU)
		ret = initialize_menu_setup(setup);
	return (ret);
}

//0 1 3 4  5
// static void	init_map_table(t_canvas_init_entry *table)
// {
// 	table[0] = (t_canvas_init_entry){
// 		.size = (t_point2i){{MAP_CANVAS_SIZE_X, MAP_CANVAS_SIZE_Y}},
// 		.type = MAP,
// 		.z_index = MAP_Z_INDEX, .position = (t_point2i){{0, 0}}, .stack = false};
// 	table[1] = (t_canvas_init_entry){
// 		.size = (t_point2i){{UI_CANVAS_SIZE_X, UI_CANVAS_SIZE_Y}}, .type = UI,
// 		.z_index = UI_Z_INDEX, .position = (t_point2i){{0, 0}}, .stack = false};
// 	table[2] = (t_canvas_init_entry){
// 		.size = (t_point2i){{MAP_CANVAS_SIZE_X - UI_CANVAS_SIZE_X, 100}}, .type = UI,
// 		.z_index = UI_Z_INDEX + 1, .position = (t_point2i){{UI_CANVAS_SIZE_X, 800}}, .stack = false};
// 	table[3] = (t_canvas_init_entry){
// 		.size = (t_point2i){{FIN_CANVAS_SIZE_X, FIN_CANVAS_SIZE_Y}},
// 		.type = FINAL,
// 		.z_index = -2, .position = (t_point2i){{0, 0}}};
// 	table[4] = (t_canvas_init_entry){
// 		.size = (t_point2i){{MAP_CANVAS_SIZE_X, MAP_CANVAS_SIZE_Y}},
// 		.type = FIN_TEMP, .z_index = -2,
// 		.position = (t_point2i){{0, 0}}};
// 	table[5] = (t_canvas_init_entry){.type = END_MARKER, .z_index = -99};
// }

static void	init_map_table(t_canvas_init_entry *table)
{
	ft_memcpy(table, g_canvas_init_table, sizeof(g_canvas_init_table));
}

int	initialize_map_editor_setup(t_setup_by_game_state *setup)
{
	static t_canvas_init_entry	canvas_init_table[6];
	t_point2i					current_pos;
	int							current_row_height;
	size_t						i;

	init_map_table(canvas_init_table);
	setup->game_state = MAP_EDITOR;
	setup->canvas_configurations = ft_calloc(sizeof(canvas_init_table)
			/ (sizeof(t_canvas_init_entry) - 1), sizeof(t_canvas_init_entry));
	if (!setup->canvas_configurations)
		return (1);
	current_pos = (t_point2i){{0, 0}};
	current_row_height = 0;
	i = 0;
	while (i < sizeof(canvas_init_table) / (sizeof(t_canvas_init_entry) - 1))
	{
		setup->canvas_configurations[i] = canvas_init_table[i];
		set_canvas_bounds(&setup->canvas_configurations[i], &current_pos,
			&current_row_height, 1920);
		i++;
	}
	return (0);
}
