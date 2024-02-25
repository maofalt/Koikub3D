/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:02:48 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/25 02:25:16 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "limits.h"
#include "libft.h"
#include "structures.h"

void	destroy_dijkstra(t_dijkstra *dijkstra)
{
	free(dijkstra->distances);
	free(dijkstra->previous);
	free(dijkstra->visited);
	dijkstra->graph_size = 0;
	dijkstra->distances = NULL;
	dijkstra->previous = NULL;
	dijkstra->visited = NULL;
}

void	reset_graph_data(t_dijkstra *dijkstra)
{
	const int	graph_size = dijkstra->graph_size;
	int			i;

	i = 0;
	while (i < graph_size)
	{
		dijkstra->distances[i] = INT_MAX;
		dijkstra->previous[i] = -1;
		dijkstra->visited[i] = 0;
		i++;
	}
}

int	dijkstra_init(t_dijkstra *dijkstra, int graph_size)
{
	ft_memset(dijkstra, 0, sizeof(t_dijkstra));
	dijkstra->graph = (int *)malloc(sizeof(int) * graph_size * graph_size);
	dijkstra->distances = (int *)malloc(sizeof(int) * graph_size);
	dijkstra->previous = (int *)malloc(sizeof(int) * graph_size);
	dijkstra->visited = (int *)malloc(sizeof(int) * graph_size);
	dijkstra->graph_size = graph_size;
	if (!dijkstra->graph || !dijkstra->distances
		|| !dijkstra->previous || !dijkstra->visited)
	{
		destroy_dijkstra(dijkstra);
		return (1);
	}
	reset_graph_data(dijkstra);
	return (0);
}


int		find_min_distance(t_dijkstra *dijkstra)
{
	const int	graph_size = dijkstra->graph_size;
	int			i;
	int			min_distance;
	int			min_index;

	i = 0;
	min_distance = INT_MAX;
	min_index = -1;
	while (i < graph_size)
	{
		if (dijkstra->visited[i] == 0 && dijkstra->distances[i] <= min_distance)
		{
			min_distance = dijkstra->distances[i];
			min_index = i;
		}
		i++;
	}
	return (min_index);
}



void	dijkstra(t_dijkstra *dijkstra, int start)
{
	const int	graph_size = dijkstra->graph_size;
	int	i;

	reset_graph_data(dijkstra);
	dijkstra->distances[start] = 0;
	i = 0;
	while (i < graph_size - 1)
	{
		const int	current = find_min_distance(dijkstra);
		dijkstra->visited[current] = 1;
		int	v = 0;
		while (v < graph_size)
		{
			if (dijkstra->visited[v] == 0
				&& dijkstra->graph[current * graph_size + v]
				&& dijkstra->distances[current]
				+ dijkstra->graph[current * graph_size + v]
				< dijkstra->distances[v])
			{
				dijkstra->distances[v] = dijkstra->distances[current]
					+ dijkstra->graph[current * graph_size + v];
				dijkstra->previous[v] = current;
			}
			v++;
		}
		i++;
	}
}


// void	fill_dijkstra_graph_from_bsp(t_dijkstra *dijkstra, t_bsp *bsp)
// {
// 	const int	graph_size = dijkstra->graph_size;
// 	int			i;

// 	i = 0;
// 	while (i < graph_size * graph_size)
// 	{
// 		dijkstra->graph[i] = 0;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < bsp->nb_nodes)
// 	{
// 		const t_bsp_node	*node = &bsp->nodes[i];
// 		const int			left = node->left;
// 		const int			right = node->right;
// 		if (left != -1)
// 			dijkstra->graph[i * graph_size + left] = 1;
// 		if (right != -1)
// 			dijkstra->graph[i * graph_size + right] = 1;
// 		i++;
// 	}
// }
