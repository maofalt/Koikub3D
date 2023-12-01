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

#include "assets.h"

static const	char *g_ui_asset_paths[ASSET_COUNT]
	= {
[WINDOW_BASE] = ASSETS_BASE_PATH "Window_Base.xpm",
[WINDOW_HEADER_INACTIVE] = ASSETS_BASE_PATH "Window_Header_Inactive.xpm",
[WINDOW_HEADER_RESIZABLE_INACTIVE]
	= ASSETS_BASE_PATH "Window_Header_Resizable_Inactive.xpm",
[WINDOW_HEADER_RESIZABLE] = ASSETS_BASE_PATH "Window_Header_Resizable.xpm",
[WINDOW_HEADER] = ASSETS_BASE_PATH "Window_Header.xpm",
[WINDOWS_BUTTON_FOCUS_OUTLINED]
	= ASSETS_BASE_PATH "Windows_Button_Focus_Outlined.xpm",
[WINDOWS_BUTTON_FOCUS] = ASSETS_BASE_PATH "Windows_Button_Focus.xpm",
[WINDOWS_BUTTON_INACTIVE] = ASSETS_BASE_PATH "Windows_Button_Inactive.xpm",
[WINDOWS_BUTTON_PRESSED_OUTLINED]
	= ASSETS_BASE_PATH "Windows_Button_Pressed_Outlined.xpm",
[WINDOWS_BUTTON_PRESSED] = ASSETS_BASE_PATH "Windows_Button_Pressed.xpm",
[WINDOWS_BUTTON] = ASSETS_BASE_PATH "Windows_Button.xpm",
[WINDOWS_DIVIDER_LINE] = ASSETS_BASE_PATH "Windows_Divider_Line.xpm",
[WINDOWS_EXAMPLE_ITCHPIC] = ASSETS_BASE_PATH "Windows_Example_ItchPic.xpm",
[WINDOWS_EXAMPLE_MAIN] = ASSETS_BASE_PATH "Windows_Example_Main.xpm",
[WINDOWS_EXAMPLE_POPUP] = ASSETS_BASE_PATH "Windows_Example_Popup.xpm",
[WINDOWS_ICONS] = ASSETS_BASE_PATH "Windows_Icons.xpm",
[WINDOWS_INNER_FRAME_INVERTED]
	= ASSETS_BASE_PATH "Windows_Inner_Frame_Inverted.xpm",
[WINDOWS_INNER_FRAME] = ASSETS_BASE_PATH "Windows_Inner_Frame.xpm",
[WINDOWS_PROGRESS_FILL] = ASSETS_BASE_PATH "Windows_Progress_Fill.xpm",
[WINDOWS_RATIO_INACTIVE] = ASSETS_BASE_PATH "Windows_Ratio_Inactive.xpm",
[WINDOWS_RATIO_SELECTED] = ASSETS_BASE_PATH "Windows_Ratio_Selected.xpm",
[WINDOWS_RATIO] = ASSETS_BASE_PATH "Windows_Ratio.xpm",
[WINDOWS_SIDEBAR_UNDERSIDE] = ASSETS_BASE_PATH "Windows_SideBar_Underside.xpm",
[WINDOWS_SLIDER_BACKGROUND] = ASSETS_BASE_PATH "Windows_Slider_Background.xpm",
[WINDOWS_SLIDER_HANDLE] = ASSETS_BASE_PATH "Windows_Slider_Handle.xpm",
[WINDOWS_TOGGLE_ACTIVE] = ASSETS_BASE_PATH "Windows_Toggle_Active.xpm",
[WINDOWS_TOGGLE_INACTIVE] = ASSETS_BASE_PATH "Windows_Toggle_Inactive.xpm",
[WINDOWS_TOGGLE_SELECTED] = ASSETS_BASE_PATH "Windows_Toggle_Selected.xpm"
};

t_img_data	*get_ui_asset(t_ui_assets asset_enum, t_img_data *ui_images)
{
	if (asset_enum < 0 || asset_enum >= ASSET_COUNT)
		return (NULL);
	return (&ui_images[asset_enum]);
}

int	initialize_and_preload_assets(t_cub *data)
{
	if (data->mlx_ptr == NULL)
		return (1);
	return (load_ui_assets(data->mlx_ptr, data->ui_images, g_ui_asset_paths));
}


int	load_ui_assets(void *mlx_ptr, t_img_data *ui_images, const char **paths)
{
	int		index;
	int		width;
	int		height;

	index = 0;
	while (index < ASSET_COUNT)
	{
		printf("load_ui_assets %d\n", index);
		printf("load_ui_assets %s\n", paths[index]);
		ui_images[index].mlx_img = mlx_xpm_file_to_image(mlx_ptr,
				(char *)paths[index], &width, &height);
		if (ui_images[index].mlx_img == NULL)
			return (printf("Error\nCould not load asset %s\n", paths[index]), 1);
		ui_images[index].addr = mlx_get_data_addr(ui_images[index].mlx_img,
				&ui_images[index].bpp, &ui_images[index].line_len,
				&ui_images[index].endian);
		ui_images[index].size = (t_vector_i){width, height};
		index++;
	}
	printf("all assets loaded succesfully\n");
	return (0);
}
