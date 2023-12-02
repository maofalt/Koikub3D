/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:24:57 by motero            #+#    #+#             */
/*   Updated: 2023/10/14 19:21:52 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ASSETS_H
# define ASSETS_H

# include <mlx.h>
# include "structures.h"
# define ASSETS_BASE_PATH "assets/gui/RetroWindowsGUI/"

/*############################################################################*/
/*                             		ASSETS                                    */
/*############################################################################*/

int			load_ui_assets(
				void *mlx_ptr,
				t_img_data *ui_images,
				const char **paths);
int			initialize_and_preload_assets(t_cub *data);
t_img_data	*get_ui_asset(t_ui_assets asset_enum, t_img_data *ui_images);

#endif