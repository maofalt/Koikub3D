/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:01:22 by motero            #+#    #+#             */
/*   Updated: 2023/10/13 22:23:53 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include <stdlib.h>
# include <stdint.h>
# include "structures.h"

/*############################################################################*/
/*                          COLOR FUNCTIONS                                   */
/*############################################################################*/

typedef union u_color
{
	t_color			rgb_color;
	struct
	{
		u_int8_t	a;
		u_int8_t	r;
		u_int8_t	g;
		u_int8_t	b;
	};
}	t_color;

/*############################################################################*/
/*                          COLOR FUNCTIONS                                   */
/*############################################################################*/
/* Encode of 4 unint8_t into a utin32_t, so mlx is able to read RGB in Hex,**
** thourgh bit shifting. */
uint32_t	encode_rgb(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue);

#endif
