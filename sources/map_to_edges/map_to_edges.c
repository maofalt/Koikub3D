/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_edges.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:21:17 by motero            #+#    #+#             */
/*   Updated: 2023/10/08 21:48:10 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "map_to_edges.h"

void	explore_edge(t_edge_exploration_context *context)
{
	t_point2d		*coord;
	t_point2d		*delta;
	t_segment_d		*segment;

	coord = &(context->coord);
	delta = &(context->delta);
	segment = &(context->segment);
	if (coord->x < 0 || coord->y < 0)
		return ;
	if (context->map[(int)coord->y][(int)coord->x] != '1')
		return ;
	if (context->visited[(int)coord->y][(int)coord->x] & context->direction)
		return ;

	context->visited[(int)coord->y][(int)coord->x] |= context->direction;
	segment->point_b.x = coord->x;
	segment->point_b.y = coord->y;
	coord->x += delta->x;
	coord->y += delta->y;
	explore_edge(context);
}


int	extract_edge_recursively(char **map, t_list **edges)
{
	t_edge_exploration_context	context;
	const int					height_map = get_map_height(map);
	const int					width_map = get_map_width(map);

	context.map = map;
	*edges = NULL;
	context.visited = malloc2DArray(map);
	if (context.visited == NULL)
		return (1);
	if (process_map(&context, edges, height_map, width_map))
		return (1);
	//free2DArray(visited);
	return (0);
}

int	process_map(t_edge_exploration_context *context, t_list **edges,
		int height_map, int width_map)
{
	int	y;
	int	x;

	y = 0;
	while (y < height_map)
	{
		x = 0;
		while (x < width_map) {
			if (context->map[y][x] == '1')
			{
				update_context(context, (t_point2d){{x, y}}, (t_point2d){{1, 0}}, RIGHT);
				explore_edge(context);
				if (context->segment.point_b.x != x || context->segment.point_b.y != y)
				{
					if (add_edge(context->segment, edges))
						return (1);
				}

				update_context(context, (t_point2d){{x, y}}, (t_point2d){{0, 1}}, DOWN);
				explore_edge(context);
				if (context->segment.point_b.x != x || context->segment.point_b.y != y)
				{
					if (add_edge(context->segment, edges))
						return (1);
				}

				update_context(context, (t_point2d){{x, y}}, (t_point2d){{1, 1}}, DIAGONAL_RIGHT);
				explore_edge(context);
				if (context->segment.point_b.x != x || context->segment.point_b.y != y)
				{
					if (add_edge(context->segment, edges))
						return (1);
				}

				update_context(context, (t_point2d){{x, y}}, (t_point2d){{-1, 1}}, DIAGONAL_LEFT);
				explore_edge(context);
				if (context->segment.point_b.x != x || context->segment.point_b.y != y)
				{
					if (add_edge(context->segment, edges))
						return (1);
				}
			}
			x++;
		}
		y++;
	}
	return (0);
}


void	update_context(t_edge_exploration_context *context, t_point2d coord,
			t_point2d delta, t_direction dir)
{
	context->coord = coord;
	context->delta = delta;
	context->segment = (t_segment_d){context->coord, context->coord};
	context->direction = dir;
}


//Add new segment to the list of edges by creating a new node and pushing it front
int add_edge(t_segment_d new_segment, t_list **edges) {

	t_list *new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL) {
		printf("Error: malloc failed\n");
		return 1; 
	}
	new_node->content = malloc(sizeof(t_segment_d));
	if (new_node->content == NULL) {
		printf("Error: malloc failed\n");
		return 1;
	}
	ft_memset(new_node->content, 0, sizeof(t_segment_d));
	if (ft_memcpy(new_node->content, &new_segment, sizeof(t_segment_d)) == NULL) {
		printf("Error: memcpy failed\n");
		return 1;
	}
	ft_lstadd_front(edges, new_node);
   return 0; 
}

//create a t_direction  table on 2d of same size of char map that is also passed as parameter
//and fill it with 0
t_direction **malloc2DArray(char **map) {

	t_direction **array;
	int         i;
	const int   size = get_map_height(map);
	
	array = ft_calloc(size, sizeof(t_direction *));
	if (array == NULL) {
		printf("Error: malloc failed\n");
		return NULL;
	}

	i = 0;
	while (i < size) {
		array[i] = ft_calloc(ft_strlen(map[i]), sizeof(t_direction));
		if (array[i] == NULL) {
			printf("Error: malloc failed\n");
			//erase Array build until now
			while (i > 0) {
				free(array[i]);
				i--;
			}
			free(array);
			return NULL;
		}
		i++;
	}

	return array;
}

