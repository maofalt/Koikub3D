/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:07:02 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/14 20:24:17 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "structures.h"
#include "map_to_edges.h"
#include "bsp_builder.h"

int	draw_map_segments(t_cub *data, t_list *segments_lst)
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

int	map_visualizer_render(t_cub *data)
{
	t_list	*segments_lst;
	t_list	*left = NULL;
	t_list	*right = NULL;

	if (data->win_ptr == NULL)
		return (1);
	segments_lst = NULL;
	if (extract_edge_recursively(data->map, &segments_lst))
		return (1);
	(void)left;
	(void)right;
	construct_bsp(&segments_lst, &left, &right);
	// printf("##########%p\n", segments_lst->content);
	draw_map_segments(data, segments_lst);
	draw_map_segments(data, left);
	draw_map_segments(data, right);
	ft_lstclear(&segments_lst, free);
	if (left)
		ft_lstclear(&left, free);
	if (right)
		ft_lstclear(&right, free);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->screen.mlx_img, 0, 0);
	printf("--------------------------------\n");
	usleep(100000);
	return (0);
}
