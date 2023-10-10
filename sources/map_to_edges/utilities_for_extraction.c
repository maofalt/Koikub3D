/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_for_extraction.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:21:17 by motero            #+#    #+#             */
/*   Updated: 2023/10/10 19:59:12 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "map_to_edges.h"


int	process_direction(t_edge_exploration_context *context, t_list **edges,
		t_point2d delta, t_direction dir)
{
	update_context(context, context->current_coord, delta, dir);
	explore_edge(context);
	if (context->segment.point_b.x != context->current_coord.x
		|| context->segment.point_b.y != context->current_coord.y)
	{
		if (add_edge(context->segment, edges))
			return (1);
	}
	return (0);
}

//Add new segment to the list of edges by creating a new node and pushing
int add_edge(t_segment_d new_segment, t_list **edges)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
	{
		printf("Error: malloc failed\n");
		return (1); 
	}
	new_node->content = malloc(sizeof(t_segment_d));
	if (new_node->content == NULL)
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	ft_memset(new_node->content, 0, sizeof(t_segment_d));
	if (ft_memcpy(new_node->content, &new_segment, sizeof(t_segment_d)) == NULL)
	{
		printf("Error: memcpy failed\n");
		return (1);
	}
	ft_lstadd_front(edges, new_node);
	return (0);
}

//create a t_direction  table on 2d of same size of char map tha
// is also passed as parameter
//and fill it with 0
t_direction	**malloc2DArray(char **map)
{
	int			i;
	t_direction	**array;
	const int	size = get_map_height(map);

	array = ft_calloc(size, sizeof(t_direction *));
	if (array == NULL)
		return (printf("Error: malloc failed\n"), NULL);
	i = 0;
	while (i < size)
	{
		array[i] = ft_calloc(ft_strlen(map[i]), sizeof(t_direction));
		if (array[i] == NULL)
		{
			printf("Error: malloc failed\n");
			while (i > 0)
			{
				free(array[i]);
				i--;
			}
			return (free(array), NULL);
		}
		i++;
	}
	return (array);
}

//Free the 2d array of t_direction
void	free2DArray(t_direction **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
