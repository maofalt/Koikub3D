/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_canvas_setups.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/12/03 23:06:02 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

const t_canvas_init_entry	g_canvas_init_table[]
	= {
[0] = {
	.type = MAP,
	.size = (t_point2i){{MAP_CANVAS_SIZE_X, MAP_CANVAS_SIZE_Y}},
	.position = (t_point2i){{0, 0}},
	.stack = false,
	.is_dynamic = false,
	.z_index = MAP_Z_INDEX,
	.event_handlers = {
	.on_keypress = &map_canvas_handle_keypress,
	.on_boutonpress = &map_canvas_handle_boutonpress,
	.render = &map_editor_render
}
},
[1] = {
	.size = (t_point2i){{UI_CANVAS_SIZE_X, UI_CANVAS_SIZE_Y - 60}},
	.type = BUTTON,
	.z_index = UI_Z_INDEX,
	.position = (t_point2i){{0, 0}},
	.stack = false,
	.fit_mode = FIT_IMAGE_TO_CANVAS,
	.asset = SIDE_BAR,
	.text = "EDIT MAP",
	.event_handlers = {
	.on_keypress = &mlx_int_do_nothing,
	.on_boutonpress = &mlx_int_do_nothing,
	.render = &button_render}},
[2] = {
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
[3] = {
	.size = (t_point2i){{FIN_CANVAS_SIZE_X, FIN_CANVAS_SIZE_Y}},
	.type = FINAL,
	.z_index = -2,
	.position = (t_point2i){{0, 0}}
},
[4] = {
	.size = (t_point2i){{MAP_CANVAS_SIZE_X, MAP_CANVAS_SIZE_Y}},
	.type = FIN_TEMP,
	.z_index = -2,
	.position = (t_point2i){{0, 0}}
},
[5] = {.type = END_MARKER, .z_index = -99}
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
			&current_row_height, WINDOW_WIDTH);
		i++;
	}
	return (0);
}
