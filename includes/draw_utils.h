/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:53:46 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/13 23:45:19 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_UTILS_H
# define DRAW_UTILS_H

# include "mlx.h"
# include "structures.h"
# include "colors.h"

/*############################################################################*/
/*                              GEOMETRY STRUTURE                             */
/*############################################################################*/

typedef enum e_shape_type
{
	LINE,
	RECTANGLE,
	CIRCLE,
	TRIANGLE
}	t_shape_type;

// LINE
typedef struct s_line_params {
	t_point2d	start;
	union
	{
		t_point2d	end;
		double		length;
	};
}	t_line_params;

// Rectangle
typedef struct s_rectangle_params {
	t_point2d	top_left;
	t_point2d	top_right;
	t_point2d	bottom_left;
	t_point2d	bottom_right;
}	t_rectangle_params;

// Circle
typedef struct s_circle_params {
	t_point2d	center;
	int			radius;
}	t_circle_params;

// Triangle
typedef struct s_triangle_params {
	t_point2d	pt1;
	t_point2d	pt2;
	t_point2d	pt3;
}	t_triangle_params;

typedef union u_shape
{
	t_line_params		line;
	t_rectangle_params	rect;
	t_circle_params		circle;
	t_triangle_params	triangle;	
}	t_shape;

typedef struct s_shape_params {
	t_img_data		*img;
	t_shape_type	shape_type;
	t_color			color;
	t_shape			shape;
}	t_shape_params;

/*############################################################################*/
/*                              DRAW FUNCTIONS                                */
/*############################################################################*/

void	img_pix_put(t_img_data *img, int x, int y, int color);
void	draw_segment(
			t_img_data *img,
			t_segment_d const *const segment,
			int color
			);
void	draw_one_line(
			t_img_data *img,
			t_line_params const *const segment,
			t_color color
			);

/*############################################################################*/
/*                              DRAW SHAPES                                */
/*############################################################################*/
int		draw_line(t_shape_params *params);
int		draw_rectangle(t_shape_params *params);
void	draw_circle_points(t_img_data *img,
			t_point2i center,
			t_point2i point,
			t_color color);
int		draw_circle(t_shape_params *params);

#endif
