/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_specialized_canvas.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 00:25:30 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

void	free_map_editor(t_canvas *canvas)
{
	t_map_editor_data	*map_editor;

	map_editor = &canvas->data.map_editor;
	if (!map_editor)
		return ;
	if (map_editor->matrix_operations)
		ft_lstclear(&map_editor->matrix_operations, free);
}

void	free_ui(t_canvas *canvas)
{
	t_ui_data	*ui;

	ui = &canvas->data.ui;
	if (!ui)
		return ;
}

void	free_button(t_canvas *canvas)
{
	t_button_data	*button;

	button = &canvas->data.button;
	if (!button)
		return ;
}

void	free_game(t_canvas *canvas)
{
	t_editor_data	*game;

	game = &canvas->data.game;
	if (!game)
		return ;
}
