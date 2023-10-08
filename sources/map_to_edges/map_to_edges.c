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

void exploreEdge(t_edge_exploration_context *context) {
    t_point2d       *coord;
    t_point2d       *delta;
    t_segment_d     *segment;

    coord = &(context->coord);
    delta = &(context->delta);
    segment = &(context->segment);
    printf("Visiting %d, %d\n", (int)coord->x, (int)coord->y);
    printf("Direction: %d\n", context->direction);
    if (coord->x < 0 || coord->y < 0)
        return;  // Out of bounds
    if (context->map[(int)coord->y][(int)coord->x] != '1')
        return;  // Not a wall
    if (context->visited[(int)coord->y][(int)coord->x] & context->direction) {
        printf("Already visited from this direction\n");
        return;  // Already visited
    }

    context->visited[(int)coord->y][(int)coord->x] |= context->direction;
    segment->point_b.x = coord->x;
    segment->point_b.y = coord->y;

    // Check if we should explore diagonally
    // if (dx != 0 && dy != 0) {
    //     if (canFormDiagonal(*start, *end)) {
    //         exploreEdge(x + dx, y + dy, dx, dy, start, end, map, visited);
    //     }
    // } else {
    coord->x += delta->x;
    coord->y += delta->y;
    printf("\n");
    exploreEdge(context);
    //}
}


int extractEdgesRecursively(char** map, t_list **edges) { 
    // Initialize all to 0
    t_edge_exploration_context  context;
    const int                   height_map = get_map_height(map);
    const int                   width_map = get_map_width(map);
    t_point2i                   coord;

    context.map = map;
    *edges = NULL;
    context.visited = malloc2DArray(map);
    if (context.visited == NULL) {
        return 1;
    }
    
    coord = (t_point2i){0, 0};
    for (int y = 0; y < height_map; y++) {
        for (int x = 0; x < width_map; x++) {
            if (map[y][x] == '1' ) {
                
                context.coord = (t_point2d){x, y};
                context.delta = (t_point2d){1, 0};
                context.segment = (t_segment_d){context.coord, context.coord};
                context.direction = RIGHT;
                // Horizontal
                printf("Testing horizontal");
                exploreEdge(&context);
                if (context.segment.point_b.x != x || context.segment.point_b.y != y) {
                    if (add_edge(context.segment, edges)) {
                        return 1;
                    }
                }

                context.coord = (t_point2d){x, y};
                context.direction = DOWN;
                context.segment = (t_segment_d){context.coord, context.coord};
                context.delta = (t_point2d){0, 1};
                // Vertical
                exploreEdge(&context);
                if (context.segment.point_b.x != x || context.segment.point_b.y != y) {
                    if (add_edge(context.segment, edges)) {
                        return 1;
                    }
                }

                context.coord = (t_point2d){x, y};
                context.delta = (t_point2d){1, 1};
                context.segment = (t_segment_d){context.coord, context.coord};
                context.direction = DIAGONAL_RIGHT;
                // Diagonal bottom-right
                exploreEdge(&context);
                if (context.segment.point_b.x != x || context.segment.point_b.y != y) {
                    if (add_edge(context.segment, edges)) {
                        return 1;
                    }
                }


                context.coord = (t_point2d){x, y};
                context.delta = (t_point2d){-1, 1};
                context.segment = (t_segment_d){context.coord, context.coord};
                context.direction = DIAGONAL_LEFT;
                // Diagonal bottom-left
                exploreEdge(&context);
                if (context.segment.point_b.x != x || context.segment.point_b.y != y) {
                    if (add_edge(context.segment, edges)) {
                        return 1;
                    }
                }

            }
        }
    }

    //free2DArray(visited);
    return 0;
}

//Add new segment to the list of edges by creating a new node and pushing it front
int add_edge(t_segment_d new_segment, t_list **edges) {

    t_list *new_node;

    new_node = malloc(sizeof(t_list));
    if (new_node == NULL) {
        printf("Error: malloc failed\n");
        //ft_lstclear(edges, free);
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

