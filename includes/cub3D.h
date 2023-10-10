/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:16:07 by motero            #+#    #+#             */
/*   Updated: 2023/10/06 16:57:09 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdint.h>
# include "libft.h"
# include "get_next_line.h"
# include "structures.h"
# include "parsing.h"
# include "mlx_engine.h"
# include "draw_utils.h"
# include "bsp_visualizer.h"
# include "colors.h"
# include <math.h>
# include <mlx.h>

# ifndef FOV
#  define FOV 60
# endif

/*############################################################################*/
/*                              GENERAL FUNCTIONS                             */
/*############################################################################*/
void	free_everything(t_cub data);

#endif