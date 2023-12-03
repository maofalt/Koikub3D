/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_specialized_final_canvas.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/12/03 21:53:00 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"


t_canvas	*initialize_fin_temp_canvas(t_canvas_init_entry *entry)
{
	t_canvas	*canvas;

	canvas = common_canvas_initialization(entry);
	fill_canvas(canvas, (t_color){.d = (size_t)canvas});
	return (canvas);
}

t_canvas	*initialize_final_canvas(t_canvas_init_entry *entry)
{
	t_canvas	*canvas;

	canvas = common_canvas_initialization(entry);
	fill_canvas(canvas, (t_color){.d = (size_t)canvas});
	return (canvas);
}
