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

#include "draw_utils.h"

int	merge_canvases(t_list **canvas_list)
{
	t_canvas	*canvas;
	t_canvas	*final_canvas;
	t_list		*current_node;

	final_canvas = get_canvas_from_list(*canvas_list, FINAL);
	if (!final_canvas)
		return (1);
	current_node = *canvas_list;
	while (current_node)
	{
		canvas = (t_canvas *)current_node->content;
		printf("canvas of type %d\n", canvas->type);
		if (canvas->type == MAP || canvas->type == UI || canvas->type == GAME)
			merge_canvas(final_canvas, canvas);
		current_node = current_node->next;
	}
	return (0);
}

static bool	are_canvases_same_size(t_canvas *a, t_canvas *b)
{
	return (a->size.x == b->size.x && a->size.y == b->size.y);
}

static void	copy_canvas_line_by_line(t_canvas *final_canvas, t_canvas *src)
{
	t_point2i	src_start;
	t_point2i	src_end;
	t_point2i	dest;
	void		*src_ptr;
	void		*dest_ptr;

	src_start = src->info.bounds.top;
	dest = src_start;
	src_end.x = src->info.bounds.bottom.x;
	printf("inside copy_canvas_line_by_line\n");
	printf("src_start.y: %d\n", src_start.y);
	printf("src bounds bottom y: %d\n", src->info.bounds.bottom.y);
	while (src_start.y < src->info.bounds.bottom.y)
	{
		printf("dest.y: %d\n", dest.y);
		printf("final_canvas->size.y: %d\n", final_canvas->size.y);
		// if (dest.y >= final_canvas->size.y)
		// 	break ;
		src_ptr = src->pixels + src_start.y * src->size.x + src_start.x;
		dest_ptr = final_canvas->pixels + dest.y * final_canvas->size.x
			+ dest.x;
		printf("line size copying %ld\n",(src_end.x - src_start.x) * sizeof(t_color));
		ft_memcpy(dest_ptr, src_ptr,
			(src_end.x - src_start.x) * sizeof(t_color));
		src_start.y++;
		dest.y++;
	}
}

int	merge_canvas(t_canvas *final_canvas, t_canvas *canvas)
{
	if (are_canvases_same_size(final_canvas, canvas))
	{
		printf("merge_canvas: same size\n");
		ft_memcpy(final_canvas->pixels, canvas->pixels,
			final_canvas->size.x * final_canvas->size.y * sizeof(t_color));
	}
	else
	{
		printf("merge_canvas: different size\n");
		copy_canvas_line_by_line(final_canvas, canvas);
	}
	return (0);
}
