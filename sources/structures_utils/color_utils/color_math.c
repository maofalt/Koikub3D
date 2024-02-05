/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 04:57:27 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/04 22:14:23 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"

t_color	color_multiply_coeff(t_color color, double coeff)
{
	t_color	result;

	result.r = color.r * coeff;
	result.g = color.g * coeff;
	result.b = color.b * coeff;
	result.a = color.a * coeff;
	return (result);
}
