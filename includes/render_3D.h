/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3D.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 01:23:36 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/14 01:31:40 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "structures.h"

int		render_3d_init(t_3d_render *render,
			t_canvas *canvas,
			t_camera *camera,
			t_map_data *map)

void	render_3d_destroy(t_3d_render *render);
