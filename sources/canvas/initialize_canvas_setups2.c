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

const t_canvas_init_entry	g_canvas_init_table2[]
	= {
[0] = {
	.type = GAME,
	.size = (t_point2i){{GAME_CANVAS_SIZE_X, GAME_CANVAS_SIZE_Y - 100}},
	.z_index = GAME_Z_INDEX,
	.position = (t_point2i){{0, 100}},
	.stack = true
},
[1] = {
	.type = BUTTON,
	.size = (t_point2i){{WINDOW_WIDTH, 100}},
	.z_index = UI_Z_INDEX,
	.position = (t_point2i){{0, 0}},
	.stack = true,
	.event_handlers = {
	.on_keypress = NULL,
	.on_boutonpress = NULL,
	.render = NULL},
	.fit_mode = FIT_IMAGE_TO_CANVAS,
	.asset = ICON_DRAW,
	.text = "Hello World"
},
[2] = {
	.type = FIN_TEMP,
	.size = (t_point2i){{MAP_CANVAS_SIZE_X, MAP_CANVAS_SIZE_Y}},
	.z_index = FIN_TEMP_Z_INDEX,
	.position = (t_point2i){{0, 0}}
},
[3] = {.type = END_MARKER, .z_index = 0}
};

const t_canvas_init_entry	g_canvas_init_table_main_menu[]
	= {
[0] = {
	.type = BUTTON,
	.z_index = 1,
	.position = (t_point2i){{0, 0}},
	.size = (t_point2i){{WINDOW_WIDTH, WINDOW_HEIGHT}},
	.stack = false,
	.fit_mode = FIT_IMAGE_TO_CANVAS,
	.asset = BACKGROUND,
	.event_handlers = {
	.on_keypress = &mlx_int_do_nothing,
	.on_boutonpress = &mlx_int_do_nothing,
	.render = &button_render}},
[1] = {
	.type = BUTTON,
	.z_index = 2,
	.size = (t_point2i){{64, 64}},
	.position = (t_point2i){{60, 650}},
	.stack = false,
	.fit_mode = FIT_IMAGE_TO_CANVAS,
	.asset = ICON_DRAW,
	.event_handlers = {
	.on_keypress = &mlx_int_do_nothing,
	.on_boutonpress = &menu_to_edit_map_handle_boutonpress,
	.render = &button_render}},

[2] = {
	.type = BUTTON,
	.size = (t_point2i){{80, 80}},
	.z_index = 2,
	.position = (t_point2i){{50, 750}},
	.stack = false,
	.fit_mode = FIT_IMAGE_TO_CANVAS,
	.asset = ICON_GAME,
	.event_handlers = {
	.on_keypress = &mlx_int_do_nothing,
	.on_boutonpress = &mlx_int_do_nothing,
	.render = &button_render}},
[3] = {
	.type = FINAL,
	.z_index = -2,
	.size = (t_point2i){{FIN_CANVAS_SIZE_X, FIN_CANVAS_SIZE_Y}},
	.position = (t_point2i){{0, 0}}},
[4] = {
	.type = FIN_TEMP,
	.z_index = -2,
	.size = (t_point2i){{MAP_CANVAS_SIZE_X, MAP_CANVAS_SIZE_Y}},
	.position = (t_point2i){{0, 0}}},
[5] = {.type = END_MARKER, .z_index = -99}
};

static void	init_gameplay_table(t_canvas_init_entry *table)
{
	ft_memcpy(table, g_canvas_init_table2, sizeof(g_canvas_init_table2));
}

int	initialize_gameplay_setup(t_setup_by_game_state *setup)
{
	static t_canvas_init_entry	canvas_init_table2[3];
	t_point2i					current_pos;
	int							current_row_height;
	size_t						i;

	init_gameplay_table(canvas_init_table2);
	setup->game_state = GAMEPLAY;
	setup->canvas_configurations = ft_calloc(sizeof(canvas_init_table2)
			/ (sizeof(t_canvas_init_entry) - 1), sizeof(t_canvas_init_entry));
	if (!setup->canvas_configurations)
		return (1);
	current_pos = (t_point2i){{0, 0}};
	current_row_height = 0;
	i = 0;
	while (i < sizeof(canvas_init_table2) / (sizeof(t_canvas_init_entry) - 1))
	{
		setup->canvas_configurations[i] = canvas_init_table2[i];
		set_canvas_bounds(&setup->canvas_configurations[i], &current_pos,
			&current_row_height, WINDOW_WIDTH);
		i++;
	}
	return (0);
}

static void	init_menu_table(t_canvas_init_entry *table)
{
	ft_memcpy(table, g_canvas_init_table_main_menu,
		sizeof(g_canvas_init_table_main_menu));
}

int	initialize_menu_setup(t_setup_by_game_state *setup)
{
	static t_canvas_init_entry	canvas_init_table3[6];
	t_point2i					current_pos;
	int							current_row_height;
	size_t						i;

	init_menu_table(canvas_init_table3);
	setup->game_state = MENU;
	setup->canvas_configurations = ft_calloc(sizeof(canvas_init_table3)
			/ (sizeof(t_canvas_init_entry) - 1), sizeof(t_canvas_init_entry));
	if (!setup->canvas_configurations)
		return (1);
	current_pos = (t_point2i){{0, 0}};
	current_row_height = 0;
	i = 0;
	while (i < sizeof(canvas_init_table3) / (sizeof(t_canvas_init_entry) - 1))
	{
		setup->canvas_configurations[i] = canvas_init_table3[i];
		set_canvas_bounds(&setup->canvas_configurations[i], &current_pos,
			&current_row_height, WINDOW_WIDTH);
		i++;
	}
	return (0);
}

size_t	get_init_table_size(t_canvas_init_entry *table)
{
	size_t	i;

	i = 0;
	while (table[i].type != END_MARKER)
	{
		i++;
	}
	return (i);
}
