/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_edges.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:21:17 by motero            #+#    #+#             */
/*   Updated: 2023/10/08 18:52:14 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "map_to_edges.h"

void exploreEdge(t_edge_exploration_context *context) {
    t_point2d       coord;
    t_point2d       delta;
    t_segment_d     segment;
    

    if (coord->x < 0 || coord->x >= WIDTH || coord->y < 0 || coord->y >= HEIGHT) {
        return;  // Out of bounds
    }
    if (context->map[y][x] != '1') {
        return;  // Not a wall
    }
    if (context->visited[y][x]) {
        return;  // Already visited
    }

    context->visited[y][x] = 1;
    segment->point_b.x = x;
    segment->point_b.y = y;

    // Check if we should explore diagonally
    // if (dx != 0 && dy != 0) {
    //     if (canFormDiagonal(*start, *end)) {
    //         exploreEdge(x + dx, y + dy, dx, dy, start, end, map, visited);
    //     }
    // } else {
    coord->x += delta->x;
    coord->y += delta->xdy;
    exploreEdge(context);
    //}
}


int extractEdgesRecursively(char** map) {
    int**                       visited = create2DArray(WIDTH, HEIGHT);  // Initialize all to 0
    t_edge_exploration_context  context;
    t_list                      *edges = NULL;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (map[y][x] == '1' && !visited[y][x]) {
                
                context.coord = (t_point2d){x, y};
                context.delta = (t_point2d){1, 0};
                context.segment = (t_segment_d){(t_v2d)context.coord, (t_v2d)context.coord};
                context.map = map;
                context.visited = visited;
                // Horizontal
                exploreEdge(&context);
                if (end.x != x || end.y != y) {
                    if (addEdgeWithIntersection(context.segment, &edges)) {
                        return 1;
                    }
                }

                context.delta = (t_point2d){0, 1};
                // Vertical
                exploreEdge(&context);
                if (end.x != x || end.y != y) {
                    if (addEdgeWithIntersection(context.segment, &edges)) {
                        return 1;
                    }
                }

                // // Diagonal bottom-right
                // exploreEdge(x + 1, y + 1, 1, 1, &start, &end, map, visited);
                // if (end.x != x || end.y != y) {
                //     addEdgeWithIntersection(start, end);
                // }

                // // Diagonal bottom-left
                // exploreEdge(x - 1, y + 1, -1, 1, &start, &end, map, visited);
                // if (end.x != x || end.y != y) {
                //     addEdgeWithIntersection(start, end);
                // }
            }
        }
    }

    free2DArray(visited);
    return 0;
}

//Add new segment to the list of edges by creating a new node and pushing it front
int addEdge(t_segment_d new_segment, t_list **edges) {

    t_list *new_node = malloc(sizeof(t_list));
    if (new_node == NULL) {
        printf("Error: malloc failed\n");
        ft_lstclear(edges, free);
        return 1; 
    }

    new_node->content = malloc(sizeof(t_segment_d));
    if (new_node->content == NULL) {
        printf("Error: malloc failed\n");
        ft_li
        return 1;
    }

    ft_memset(new_node->content, 0, sizeof(t_segment_d));
    if (ft_memcpy(new_node->content, &new_segment, sizeof(t_segment_d)) == NULL) {
        printf("Error: memcpy failed\n");
        return 1;
    }
    new_node->next = *edges;
    *edges = new_node;

   return 0; 
}
