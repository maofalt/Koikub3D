/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:03:06 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/23 00:59:27 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_LOOP_H
# define GAME_LOOP_H

# include "structures.h"

int		game_init(t_cub *data, t_canvas *canvas);
void	game_render(t_cub *data);
void	game_update(t_cub *data);
int		game_loop(void *self, t_cub *data);
void	game_post_process_frame(t_3d_render *render);

void	player_handle_event(t_cub *data, t_game_data *game_data);
void	game_update_camera(t_game_data *data);

int		game_render_init(t_cub *data, t_game_data *game_data, t_canvas *canvas);
void	game_render_destroy(t_cub *data, t_game_data *game_data);

void	count_fps(void);

#endif
