/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 03:57:17 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/16 06:37:40 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "engine.h"
#include "map_to_edges.h"
// #include "bsp_builder.h"

void	fill_image(t_img_data *image, int color)
{
	char				*px;
	unsigned long long	image_size;

	px = image->addr;
	image_size = image->line_len * image->size[1] / image->bpp * 8;
	while (image_size > 0)
	{
		*(unsigned int *)px = color;
		px += image->bpp / 8;
		image_size --;
	}
}


int	draw_player(t_cub *data)
{
	t_segment_d	scaled_segment;

	scaled_segment.point_a = data->player.pos;
	scaled_segment.point_b.vec = data->player.pos.vec + data->player.dir.vec;
	scaled_segment.point_a.vec *= 10;
	scaled_segment.point_b.vec *= 10;
	draw_segment(&data->screen, &scaled_segment,
		0xFFFFFFFF);
	return (0);
}

int	draw_map(t_cub *data, t_list *segments_lst)
{
	t_segment_d	scaled_segment;

	while (segments_lst != NULL)
	{
		scaled_segment = *(t_segment_d *)segments_lst->content;
		scaled_segment.point_a.vec *= 10;
		scaled_segment.point_b.vec *= 10;
		draw_segment(&data->screen, &scaled_segment,
			(size_t)(void *)segments_lst);
		segments_lst = segments_lst->next;
	}
	return (0);
}

int	render(t_cub *data)
{
	t_list	*segments_lst;

	if (data->win_ptr == NULL)
		return (1);
	segments_lst = NULL;
	if (extract_edge_recursively(data->map, &segments_lst))
		return (1);
	player_handle_event(data);
	fill_image(&data->screen, 0x00000000);
	draw_map(data, segments_lst);
	draw_player(data);
	ft_lstclear(&segments_lst, free);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->screen.mlx_img, 0, 0);
	usleep(10000);
	return (0);
}
