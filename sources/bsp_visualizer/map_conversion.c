/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 23:29:11 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/07 23:35:53 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "structures.h"

t_list	*create_segment_node(void)
{
	t_segment_d	*segment;
	t_list		*node;

	segment = malloc(sizeof(t_segment_d));
	if (segment == NULL)
		return (NULL);
	node = ft_lstnew(segment);
	if (node == NULL)
	{
		free(segment);
		return (NULL);
	}
	return (node);
}

t_list	*create_initialized_segment_node(t_segment_d segment)
{
	t_list	*node;

	node = create_segment_node();
	if (node != NULL)
	{
		*(t_segment_d *)node->content = segment;
	}
	return (node);
}

int	add_segment_to_lst(t_list **lst, t_segment_d segment)
{
	t_list	*node;

	node = create_initialized_segment_node(segment);
	if (!node)
		return (1);
	ft_lstadd_front(lst, node);
	return (0);
}

int	convert_map_to_segments(t_cub *data, t_list **segment_lst)
{
	size_t		x;
	size_t		y;
	t_segment_d	segment;

	y = 0;
	while (data->map[y + 1] != NULL)
	{
		x = 0;
		while (data->map[y][x + 1] != '\0')
		{
			if (((data->map[y][x] ^ '0') ^ (data->map[y][x + 1] ^ '0')) == 1)
			{
				segment = (t_segment_d){{{x + 1, y}}, {{x + 1, y + 1}}};
				add_segment_to_lst(segment_lst, segment);
			}
			if (((data->map[y][x] ^ '0') ^ (data->map[y + 1][x] ^ '0')) == 1)
			{
				segment = (t_segment_d){{{x, y + 1}}, {{x + 1, y + 1}}};
				add_segment_to_lst(segment_lst, segment);
			}
			++x;
		}
		++y;
	}
	return (0);
}
