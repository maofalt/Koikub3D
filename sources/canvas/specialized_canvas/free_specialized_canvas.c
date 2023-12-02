/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/16 17:43:36 by motero           ###   ########.fr       */
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
	if (map_editor->segments)
		ft_lstclear(&map_editor->segments, free);
	//aligned_free(map_editor);
}

void	free_ui(t_canvas *canvas)
{
	t_ui_data	*ui;

	ui = &canvas->data.ui;
	if (!ui)
		return ;
	//free(ui);
}

void	free_button(t_canvas *canvas)
{
	t_button_data	*button;

	button = &canvas->data.button;
	if (!button)
		return ;
	//free(button);
}

void	free_game(t_canvas *canvas)
{
	t_game_data	*game;

	game = &canvas->data.game;
	if (!game)
		return ;
	//free(game);
}

// void	free_fin_temp(t_fin_temp_data *fin_temp)
// {
// 	if (!fin_temp)
// 		return ;
// 	free(fin_temp);
// }

// void	free_final(t_final_data *final)
// {
// 	if (!final)
// 		return ;
// 	free(final);
// }