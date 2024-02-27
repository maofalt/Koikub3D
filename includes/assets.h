/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:24:57 by motero            #+#    #+#             */
/*   Updated: 2024/02/27 02:07:27 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# include "structures.h"
# include <mlx.h>
# define ASSETS_BASE_PATH "assets/gui/RetroWindowsGUI/"

/*############################################################################*/
/*                             		ASSETS                                    */
/*############################################################################*/

int			load_assets(void *mlx_ptr, t_img_data *ui_images,
				const char **paths, int count);
int			initialize_and_preload_assets(t_cub *data);
t_img_data	*get_ui_asset(t_ui_assets asset_enum, t_img_data *ui_images);
void		destroy_assets(t_cub *data);

#endif
