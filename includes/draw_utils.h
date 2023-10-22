/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:53:46 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/22 21:51:01 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_UTILS_H
# define DRAW_UTILS_H

# include "mlx.h"
# include "structures.h"
# include "colors.h"
# include "matrix.h"

# define MAP_CANVAS_SIZE_X 1000
# define MAP_CANVAS_SIZE_Y 1000
# define UI_CANVAS_SIZE_X 1000
# define UI_CANVAS_SIZE_Y 1000
# define FINAL_CANVAS_SIZE_X 1000
# define FINAL_CANVAS_SIZE_Y 1000

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
	FINAL,
	FINAL_TEMP
}	t_canvas_type;

typedef struct s_dirty_rect
{
	t_point2d	pos;
	t_point2d	size;
}	t_dirty_rect;

typedef struct s_canvas {
	t_canvas_type	type;
	t_matrix3x3		transformation_matrix;
	t_point2i		size;
	t_point2d		last_point;
	t_color			*pixels;
	t_list			*dirty_rects;
	t_list			*segments;
	double			pixel_scale;
	int				dirty_rect_count;
}	t_canvas;

typedef struct s_canvas_init_entry {
	t_point2i		size;
	t_canvas_type	type;
}	t_canvas_init_entry;

/*############################################################################*/
/*                              CANVAS INITIALIZATION                         */
/*############################################################################*/

t_canvas	*initialize_single_canvas(t_point2i size, t_canvas_type type);
t_list		*initialize_canvas_and_add_to_list(t_point2i size,
				t_canvas_type type,
				t_list **canvas_list);
t_list		*initialize_canvas_list(t_point2i size_map, t_point2i size_ui,
				t_point2i size_final);
void		free_canvas(t_canvas *canvas);
void		free_canvas_list(t_list *canvas_list);

t_canvas	*get_canvas_from_list(t_list *canvas_list,
				t_canvas_type type);

/*############################################################################*/
/*                              MAP CANVAS OPERATIONS                         */
/*############################################################################*/

int			add_dirty_rect(t_canvas *canvas, t_point2d coord, t_point2d size);
int			add_segment_to_map(t_canvas *canvas, t_segment_d segment);
int			erase_line_from_map(t_canvas *canvas, t_segment_d segment);
int			apply_transformation_to_map(t_canvas *canvas,
				t_matrix3x3 transform);

/*############################################################################*/
/*                              DRAWING CANVAS OPERATIONS                     */
/*############################################################################*/

void		put_pixel_on_canvas(t_canvas *canvas,
				t_point2i coord,
				t_color color);
void		put_pixel_on_virtual_canvas(t_canvas *canvas,
				t_point2d coord,
				t_color color);
int			draw_line_on_map(t_canvas *canvas,
				t_point2d start,
				t_point2d end,
				t_color color);
void		start_drawing(t_canvas *canvas, t_point2d start_point);
void		update_drawing(t_canvas *canvas,
				t_point2d current_point,
				t_color color);
void		end_drawing(t_canvas *canvas,
				t_point2d end_point,
				t_color color);

/*############################################################################*/
/*                              MULTI-BUFFER CANVAS                           */
/*############################################################################*/

t_canvas	*get_canvas(t_list *canvas_list, t_canvas_type type);

/*############################################################################*/
/*                              UI CANVAS OPERATIONS                          */
/*############################################################################*/

int			draw_UI_elements(t_canvas *ui_canvas);
void		copy_canvas_to_temp(t_list *canvas_list);
void		copy_temp_to_screen(t_list *canvas_list, t_img_data *img);
void		copy_temp_to_canvas(t_list *canvas_list);

/*############################################################################*/
/*                              FUSING CANVASES                               */
/*############################################################################*/

int			fuse_canvases(t_canvas **array_of_canvases);

/*############################################################################*/
/*                              MLX CONVERSION                                */
/*############################################################################*/

// void		canvas_to_mlx_image(t_cub *data);
void		canvas_to_mlx_image(t_img_data screen, t_canvas *final_canvas);

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
t_vector4d	point2d_to_vector4d(t_point2d *point);
t_point2d	vector4d_to_point2d(t_vector4d *vec4d);
t_vector4d	point2d_to_vector4d_cpy(t_point2d point);
t_point2d	vector4d_to_point2d_cpy(t_vector4d vec4d);

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
void		draw_segment_canvas(
				t_canvas *canvas,
				t_segment_d const *const segment,
				t_color color
				);
void		fill_canvas(
				t_canvas *canvas,
				t_color color
				);

#endif
