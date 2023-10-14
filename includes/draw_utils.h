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
# include "matrix.h"

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
/*                              CANVAS STRUCTURES                             */
/*############################################################################*/

typedef enum e_canvas_type
{
	MAP,
	UI,
	FINAL
}	t_canvas_type;

typedef struct s_dirty_rect
{
	t_v2i	pos;
	t_v2i	size;
}	t_dirty_rect;

typedef struct s_canvas {
	t_color			*pixels;
	t_v2i			size;
	t_matrix3x3		transformation_matrix;
	t_dirty_rect	*dirty_rects;
	int				dirty_rect_count;
	t_segment_d		*segments;
	t_canvas_type	type;
}	t_canvas;

/*############################################################################*/
/*                              CANVAS INITIALIZATION                         */
/*############################################################################*/

t_canvas	*initialize_canvas(t_v2i size);
void		free_canvas(t_canvas *canvas);

/*############################################################################*/
/*                              MAP CANVAS OPERATIONS                         */
/*############################################################################*/

int			add_dirty_rect(t_canvas *canvas, t_v2i coord, t_v2i size);
int			add_segment_to_map(t_canvas *canvas, t_segment_d segment);
int			draw_line_on_map(t_canvas *canvas,
				t_point2d start,
				t_point2d end,
				t_color color);
int			erase_line_from_map(t_canvas *canvas, t_segment_d segment);
int			apply_transformation_to_map(t_canvas *canvas,
				t_matrix3x3 transform);

/*############################################################################*/
/*                              UI CANVAS OPERATIONS                          */
/*############################################################################*/

int			draw_UI_elements(t_canvas *ui_canvas);

/*############################################################################*/
/*                              FUSING CANVASES                               */
/*############################################################################*/

int			fuse_canvases(t_canvas **array_of_canvases);

/*############################################################################*/
/*                              MLX CONVERSION                                */
/*############################################################################*/

void		*canvas_to_mlx_image(t_canvas *final_canvas);

/*############################################################################*/
/*                              DRAW FUNCTIONS                                */
/*############################################################################*/

void		img_pix_put(t_img_data *img, int x, int y, int color);
void		draw_segment(
				t_img_data *img,
				t_segment_d const *const segment,
				int color
				);
void		draw_one_line(
				t_img_data *img,
				t_line_params const *const segment,
				t_color color
				);

/*############################################################################*/
/*                              DRAW SHAPES                                */
/*############################################################################*/
int			draw_line(t_shape_params *params);
int			draw_rectangle(t_shape_params *params);
void		draw_circle_points(t_img_data *img,
				t_point2i center,
				t_point2i point,
				t_color color);
int			draw_circle(t_shape_params *params);

#endif
