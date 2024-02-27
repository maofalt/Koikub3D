/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources_managers.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:41:19 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 02:07:22 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESSOURCES_MANAGERS_H
# define RESSOURCES_MANAGERS_H

# include "structures.h"

// TEXTURES

void		texture_set(t_texture *texture, int frame, t_img_data *img);
int			texture_init(t_texture *texture, int frames_count,
				int ms_per_frame);
void		texture_destroy(t_texture *texture);
t_img_data	*texture_get_frame(t_texture *texture);
t_img_data	*texture_get_frame_offset(t_texture *texture, int offset);
void		texture_update(t_texture *texture, size_t dt);

void		texture_manager_update(t_texture_manager *texture_manager);
int			texture_manager_destroy(t_cub *data);
int			texture_manager_init(t_cub *data);

#endif
