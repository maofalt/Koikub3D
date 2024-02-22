/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:03:30 by motero            #+#    #+#             */
/*   Updated: 2024/02/22 09:52:52 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "dynamic_array.h"

static int	read_map(char *line, char ***map, int fd)
{
	t_dynamic_array	*array;

	array = dynamic_array_init(sizeof(char *), 2048);
	if (!array)
		return (print_error("Error malloc"), 1);
	while (line)
	{
		if (dynamic_array_add(array, &line) == NULL)
		{
			dynamic_array_destroy(array);
			print_error("Error malloc");
			return (1);
		}
		line = get_next_line(fd);
	}
	*map = malloc(sizeof(char **) * (array->size + 1));
	if (!*map)
		return (dynamic_array_destroy(array), 1);
	ft_memcpy(*map, array->buffer, array->size * sizeof(char *));
	(*map)[array->size] = NULL;
	dynamic_array_destroy(array);
	return (0);
}

/**
**while reading the file, we create a node for each line
** and add the line as a void *content to the node
** we then add the node to the list.
** we then  get the size of the list with ft_lstsize
** and we create a char ** with the size of the list
** we then add the content of each node to the char **
** and free the node
** we then return 1
 */
int	parse_map(char	*line, char ***map, int fd)
{
	return (read_map(line, map, fd) == 0);
}

/* print a char **
*/

void	print_map(char **map)
{
	int	i;

	printf("****map\n");
	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}
