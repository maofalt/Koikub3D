/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_canvas_setups2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/12/03 23:17:12 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "game_loop.h"

const t_canvas_init_entry	g_canvas_init_table2[]
	= {
[0] = {
	.type = GAME,
	.size = (t_point2i){{GAME_CANVAS_SIZE_X, GAME_CANVAS_SIZE_Y}},
	.z_index = GAME_Z_INDEX,
	.position = (t_point2i){{0, 0}},
	.stack = false,
	.event_handlers = {
	.on_keypress = &ft_handle_game_keypress,
	.on_keyrelease = &ft_handle_game_keyrelease,
	.on_boutonpress = &mlx_int_do_nothing,
	.render = &game_loop}},
[1] = {
	.size = (t_point2i){{MAP_CANVAS_SIZE_X, 60}},
	.type = BUTTON,
	.z_index = UI_Z_INDEX + 1,
	.position = (t_point2i){{0, UI_CANVAS_SIZE_Y - 60}},
	.stack = false,
	.fit_mode = FIT_IMAGE_TO_CANVAS,
	.asset = BAR_WITH_DRAW,
	.text = "TBD",
	.event_handlers = {
	.on_keypress = &mlx_int_do_nothing,
	.on_boutonpress = &mlx_int_do_nothing,
	.render = &button_render}},
[2] = {
	.type = FIN_TEMP,
	.z_index = -3,
	.size = (t_point2i){{MAP_CANVAS_SIZE_X, MAP_CANVAS_SIZE_Y}},
	.position = (t_point2i){{0, 0}}
},
[3] = {
	.type = FINAL,
	.z_index = -2,
	.size = (t_point2i){{FIN_CANVAS_SIZE_X, FIN_CANVAS_SIZE_Y}},
	.position = (t_point2i){{0, 0}}
},
[4] = {.type = END_MARKER, .z_index = 0}
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
	.on_keyrelease = &mlx_int_do_nothing,
	.on_boutonpress = &mlx_int_do_nothing,
	.render = &button_render}},
[1] = {
	.type = BUTTON,
	.z_index = 2,
	.size = (t_point2i){{122, 99}},
	.position = (t_point2i){{30, 640}},
	.stack = false,
	.fit_mode = FIT_IMAGE_TO_CANVAS,
	.asset = ICON_DRAW,
	.event_handlers = {
	.on_keypress = &mlx_int_do_nothing,
	.on_keyrelease = &mlx_int_do_nothing,
	.on_boutonpress = &menu_to_edit_map_handle_boutonpress,
	.render = &button_render}},

[2] = {
	.type = BUTTON,
	.size = (t_point2i){{87, 100}},
	.z_index = 2,
	.position = (t_point2i){{45, 775}},
	.stack = false,
	.fit_mode = FIT_IMAGE_TO_CANVAS,
	.asset = ICON_GAME,
	.event_handlers = {
	.on_keypress = &mlx_int_do_nothing,
	.on_keyrelease = &mlx_int_do_nothing,
	.on_boutonpress = &menu_to_game_handle_boutonpress,
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
	static t_canvas_init_entry	canvas_init_table2[5];
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
	while (table[i].type != END_MARKER && i < 20)
	{
		printf("table[%zu].type: %d\n", i, table[i].type);
		i++;
	}
	return (i);
}
