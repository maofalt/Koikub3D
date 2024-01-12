/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 00:44:11 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/12 21:59:40 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "structures.h"
#include "map_to_edges.h"
#include "bsp_builder.h"
#include "maths_utils.h"
#include "render_3D.h"
#include "ressources_managers.h"
#include <assert.h>



void	post_process_frame(t_3d_render *render)
{
	const int max_offset = render->canvas->size.x * render->canvas->size.y;
	int	i;

	i = 0;
	while (i < max_offset)
	{
		// if (render->z_buffer[i] >= 1)
		// {
		// 	render->canvas->pixels[i].a /= render->z_buffer[i];
		// 	render->canvas->pixels[i].r /= render->z_buffer[i];
		// 	render->canvas->pixels[i].g /= render->z_buffer[i];
		// 	render->canvas->pixels[i].b /= render->z_buffer[i];
		// }
		render->canvas->pixels[i] = shader_torch(render->canvas->pixels[i], i,
			render->canvas->size.x, render->canvas->size.y, render);
		++i;
	}
}

void	game_render(t_cub *data)
{
	t_canvas	*canvas;

	texture_manager_update(&data->texture_manager);
	canvas = data->game_data.game_view_render.canvas;
	fill_canvas(
		canvas,
		(t_color){.d = 0x00000000});
	render_3d_draw(&data->game_data.game_view_render);
	// post_process_frame(&data->game_data.game_view_render);
	// canvas_to_mlx_image(data->screen,
	// 	canvas);
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
	// 	data->screen.mlx_img, 0, 0);
}

//-----------


int	game_render_init(t_cub  *data, t_canvas *canvas)
{
	if (canvas == NULL)
		return (1);
	return (render_3d_init(&data->game_data.game_view_render, canvas,
		&data->game_data.state.player_camera, &data->game_data.map_data));
}

void	game_render_destroy(t_cub *data)
{
	render_3d_destroy(&data->game_data.game_view_render);
}

