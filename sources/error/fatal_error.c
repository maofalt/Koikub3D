/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:51:43 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/11 22:51:44 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include <stdio.h>
#include "mlx.h"

int	fatal_error(t_cub *data, char *msg)
{
	printf("Fatal error: %s\n", msg);
	mlx_loop_end(data->mlx_ptr);
	return (1);
}
