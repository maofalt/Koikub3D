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

static void	init_gameplay_table(t_canvas_init_entry *table)
{
	table[0] = (t_canvas_init_entry){
		.size = (t_point2i){{GAME_CANVAS_SIZE_X, GAME_CANVAS_SIZE_Y - 100}},
		.type = GAME, .z_index = GAME_Z_INDEX,
		.position = (t_point2i){{0, 100}}, .stack = true};
	table[1] = (t_canvas_init_entry){
		.size = (t_point2i){{1920, 100}}, .type = UI,
		.z_index = UI_Z_INDEX, .position = (t_point2i){{0, 0}}, .stack = true};
	table[2] = (t_canvas_init_entry){
		.size = (t_point2i){{MAP_CANVAS_SIZE_X, MAP_CANVAS_SIZE_Y}},
		.type = FIN_TEMP, .z_index = FIN_TEMP_Z_INDEX,
		.position = (t_point2i){{0, 0}}};
	table[3] = (t_canvas_init_entry){.type = END_MARKER, .z_index = 0};
}

int	initialize_gameplay_setup(t_setup_by_game_state *setup)
{
	static t_canvas_init_entry	canvas_init_table[3];
	t_point2i					current_pos;
	int							current_row_height;
	size_t						i;

	init_gameplay_table(canvas_init_table);
	setup->game_state = GAMEPLAY;
	setup->canvas_configurations = ft_calloc(sizeof(canvas_init_table)
			/ sizeof(t_canvas_init_entry) - 1, sizeof(t_canvas_init_entry));
	if (!setup->canvas_configurations)
		return (1);
	current_pos = (t_point2i){{0, 0}};
	current_row_height = 0;
	i = 0;
	while (i < sizeof(canvas_init_table) / sizeof(t_canvas_init_entry) - 1)
	{
		setup->canvas_configurations[i] = canvas_init_table[i];
		set_canvas_bounds(&setup->canvas_configurations[i], &current_pos,
			&current_row_height, 1920);
		i++;
	}
	return (0);
}

static void	init_menu_table(t_canvas_init_entry *table)
{
	table[0] = (t_canvas_init_entry){
		.size = (t_point2i){{1920, 1072}},
		.type = GAME, .z_index = 1, 
		.position = (t_point2i){{0, 0}}, .stack = false};
	table[1] = (t_canvas_init_entry){
		.size = (t_point2i){{500, 500}},
		.type = GAME, .z_index = 2, 
		.position = (t_point2i){{250, 250}}, .stack = false};
	table[2] = (t_canvas_init_entry){
		.size = (t_point2i){{MAP_CANVAS_SIZE_X, MAP_CANVAS_SIZE_Y}},
		.type = FIN_TEMP, .z_index = FIN_TEMP_Z_INDEX,
		.position = (t_point2i){{0, 0}}};
	table[3] = (t_canvas_init_entry){.type = END_MARKER, .z_index = 0};
}

int	initialize_menu_setup(t_setup_by_game_state *setup)
{
	static t_canvas_init_entry	canvas_init_table[5];
	t_point2i					current_pos;
	int							current_row_height;
	size_t						i;

	init_menu_table(canvas_init_table);
	setup->game_state = MENU;
	setup->canvas_configurations = ft_calloc(sizeof(canvas_init_table)
			/ sizeof(t_canvas_init_entry) - 1, sizeof(t_canvas_init_entry));
	if (!setup->canvas_configurations)
		return (1);
	current_pos = (t_point2i){{0, 0}};
	current_row_height = 0;
	i = 0;
	while (i < sizeof(canvas_init_table) / sizeof(t_canvas_init_entry) - 1)
	{
		setup->canvas_configurations[i] = canvas_init_table[i];
		set_canvas_bounds(&setup->canvas_configurations[i], &current_pos,
			&current_row_height, 1920);
		i++;
	}
	return (0);
}
