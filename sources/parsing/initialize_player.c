/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:39:01 by motero            #+#    #+#             */
/*   Updated: 2024/02/04 20:15:40 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
** intiialize the t_player structure
** 1 - intialize the position of the player into the map as a t_vector_f pos
** 2 - initialize the direction of the player as a t_vector_f dir
** 3 - initialize the plane of the player as a t_vector_f plane which represents
** the camera plane
*/
int	initialize_player(t_cub *data)
{
	initialize_player_pos(data);
	initialize_player_dir(data);
	initialize_player_plane(data);
	return (1);
}

/*
** Look for NSEW in the map and set the position of the player accorindgly
** and initialize the t_vector_f pos of the player
*/
void	initialize_player_pos(t_cub *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S' ||
				data->map[y][x] == 'E' || data->map[y][x] == 'W')
			{
				data->player.pos.x = x + 0.5;
				data->player.pos.y = y + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
}

typedef struct orientation
{
	char		orientation;
	t_vector4d	dir;
}	t_orientation;

static const t_orientation	g_orientation[] = {
{'N', {{0, -1, 0, 0}}},
{'S', {{0, 1, 0, 0}}},
{'E', {{1, 0, 0, 0}}},
{'W', {{-1, 0, 0, 0}}},
{0, {{0, 0, 0, 0}}}
};

/*
** Initialize the direction of the player as a t_vector_f dir
** depending on the position of the player in the map
** and the orientation of the player "N", "S", "E", "W"
*/

void	initialize_player_dir(t_cub *data)
{
	char	orientation;
	int		i;

	orientation = data->map[(int)data->player.pos.y][(int)data->player.pos.x];
	i = 0;
	while (g_orientation[i].orientation)
	{
		if (g_orientation[i].orientation == orientation)
		{
			data->player.dir = g_orientation[i].dir;
			return ;
		}
		++i;
	}
}

/*
** Intiialize the  camera plane which is perpendicylar to the direction of the
** player and is used to calculate the ray direction
*/
void	initialize_player_plane(t_cub *data)
{
	char	direction;

	direction = data->map[(int)data->player.pos.y][(int)data->player.pos.x];
	if (direction == 'N')
	{
		data->player.plane[0] = 0;
		data->player.plane[1] = -0.66;
	}
	else if (direction == 'S')
	{
		data->player.plane[0] = 0;
		data->player.plane[1] = 0.66;
	}
	else if (direction == 'E')
	{
		data->player.plane[0] = -0.66;
		data->player.plane[1] = 0;
	}
	else if (direction == 'W')
	{
		data->player.plane[0] = 0.66;
		data->player.plane[1] = 0;
	}
}
