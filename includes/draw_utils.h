/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:53:46 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/11 00:21:47 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_UTILS_H
# define DRAW_UTILS_H

# include <stdbool.h>
# include "mlx.h"
# include "structures.h"
# include "colors.h"
# include "matrix.h"
// # include "list_fonctions.h"
# include "mlx_engine.h"

# define MAP_CANVAS_SIZE_X 1920
# define MAP_CANVAS_SIZE_Y 1020
# define UI_CANVAS_SIZE_X 200
# define UI_CANVAS_SIZE_Y 1020
# define FIN_CANVAS_SIZE_X 1920
# define FIN_CANVAS_SIZE_Y 1020
# define GAME_CANVAS_SIZE_X 1920
# define GAME_CANVAS_SIZE_Y 1020
# define MAP_Z_INDEX 3
# define GAME_Z_INDEX 1
# define UI_Z_INDEX 5
# define FINAL_Z_INDEX 99
# define FIN_TEMP_Z_INDEX 99
# define END_MARKER_Z_INDEX 0

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
/*                            CANVAS SPECIALIZATION                           */
/*############################################################################*/

typedef struct s_map_editor_data
{
	t_list		*matrix_operations;
	t_list		*segments;
	t_matrix3x3	transformation_matrix;
	t_point2d	last_point;
}	t_map_editor_data;

typedef struct s_button_data
{
	t_ui_assets		asset;
	char			text[256];
	t_img_data		*img;
	t_color			color;
	t_img_fit_mode	fit_mode;
	int				(*action_on_click)(void *data, void *self);
}	t_button_data;

typedef struct s_ui_data
{
	t_list			*buttons;
	t_img_data		*img;
}	t_ui_data;

typedef struct s_editor_data
{
	t_list	*matrix_operations;
	t_list	*segments;
}	t_editor_data;

typedef union u_canvas_data
{
	t_map_editor_data	map_editor;
	t_button_data		button;
	t_ui_data			ui;
	t_editor_data			game;
}	t_canvas_data;

/*############################################################################*/
/*                              CANVAS STRUCTURES                             */
/*############################################################################*/


typedef struct s_bounds {
	t_point2i	top;
	t_point2i	bottom;
}	t_bounds;

typedef struct s_canvas_init_entry {
	t_canvas_type		type;
	t_point2i			size;
	t_point2i			position;
	t_bounds			bounds;
	bool				stack;
	bool				is_dynamic;
	int					z_index;
	size_t				nbr_canvas;
	t_event_handlers	event_handlers;
	t_img_fit_mode		fit_mode;
	t_ui_assets			asset;
	t_color				color;
	char				text[256];
}	t_canvas_init_entry;

typedef struct s_canvas {
	t_canvas_data		data;
	t_canvas_type		type;
	t_point2i			size;
	t_point2d			scale;
	t_point2d			inv_scale;
	t_color				*pixels;
	t_color				transparency_key;
	bool				is_dynamic;
	t_bounds			bounds;
	int					z_index;
	t_event_handlers	event_handlers;
}	t_canvas;

typedef struct s_setup_by_game_state
{
	t_modus_state		game_state;
	t_canvas_init_entry	*canvas_configurations;
	size_t				canvas_count;
}	t_setup_by_game_state;

/*############################################################################*/
/*                              CANVAS INITIALIZATION                         */
/*############################################################################*/

typedef t_canvas	*(*t_canvas_init_func)(t_canvas_init_entry *);
typedef void		(*t_canvas_free_func)(t_canvas *);

t_canvas					*initialize_canvas(
								t_canvas_init_entry *entry);
t_canvas					*common_canvas_initialization(
								t_canvas_init_entry *entry);
t_canvas					*initialize_map_editor_canvas(
								t_canvas_init_entry *entry);
t_canvas					*initialize_button_canvas(
								t_canvas_init_entry *entry);
t_canvas					*initialize_ui_canvas(
								t_canvas_init_entry *entry);
t_canvas					*initialize_game_canvas(
								t_canvas_init_entry *entry);
t_canvas					*initialize_fin_temp_canvas(
								t_canvas_init_entry *entry);
t_canvas					*initialize_final_canvas(
								t_canvas_init_entry *entry);
t_list						*initialize_canvas_and_add_to_list(
								t_canvas_init_entry *entry,
								t_list **canvas_list);
t_list						*initialize_canvas_list(t_modus_state state,
								t_setup_by_game_state *canvas_setups);

t_canvas					*get_canvas_from_list(t_list *canvas_list,
								t_canvas_type type);
t_canvas_init_entry			*get_canvas_init_table(t_modus_state state,
								t_setup_by_game_state *canvas_setups);
void						set_canvas_bounds(t_canvas_init_entry *entry,
								t_point2i *currentPos,
								int *currentRowHeight,
								int maxWidth);

/*############################################################################*/
/*                              CANVAS DESTRUCTION                            */
/*############################################################################*/
void						free_canvas(t_canvas *canvas);
void						free_canvas_list(t_list *canvas_list);
void						free_canvas_by_type(t_canvas *canvas);
void						free_map_editor(t_canvas *canvas);
void						free_ui(t_canvas *canvas);
void						free_button(t_canvas *canvas);
void						free_game(t_canvas *canvas);

/*############################################################################*/
/*                              MAP CANVAS OPERATIONS                         */
/*############################################################################*/

int							add_segment_to_map(t_map_editor_data *map_editor,
								t_segment_d segment);
int							erase_line_from_map(t_canvas *canvas,
								t_segment_d segment);
int							apply_transformation_to_map(t_canvas *canvas,
								t_matrix3x3 transform);

/*############################################################################*/
/*                              DRAWING CANVAS OPERATIONS                     */
/*############################################################################*/

void						put_pixel_on_canvas(t_canvas *canvas,
								t_point2i coord,
								t_color color);
// void						put_pixel_on_virtual_canvas(t_canvas *canvas,
// 								t_point2i coord,
// 								t_color color);
int							draw_line_on_map(t_canvas *canvas,
								t_point2i start,
								t_point2i end,
								t_color color);
void						start_drawing(t_canvas *canvas,
								t_point2i start_point);
void						update_drawing(t_canvas *canvas,
								t_point2i current_point,
								t_color color);
void						end_drawing(t_canvas *canvas,
								t_point2i end_point,
								t_color color);
int							process_key(
								int keysym,
								t_point2i pos,
								t_canvas *map_canvas);

/*############################################################################*/
/*                              MATRIX ABSTRACTIONS                           */
/*############################################################################*/
int							apply_matrix_transformation(
								t_map_editor_data *map_editor,
								t_matrix3x3 matrix);
int							apply_zoom_at_position(
								t_map_editor_data *map_editor,
								double zoom,
								t_point2d pos);
int							apply_rotation_at_position(
								t_map_editor_data *map_editor,
								double angle,
								t_point2d pos);

/*############################################################################*/
/*                              MULTI-BUFFER CANVAS                           */
/*############################################################################*/

t_canvas					*get_canvas(t_list *canvas_list,
								t_canvas_type type);

/*############################################################################*/
/*                 		CANVAS MEMBER FUNCTIONS                               */
/*############################################################################*/
int							render_base(void *canvas, t_cub *data);
void						fill_canvas_with_image(
								t_canvas *canvas,
								t_img_data *img);

/*############################################################################*/
/*                              UI CANVAS OPERATIONS                          */
/*############################################################################*/

int							draw_UI_elements(t_canvas *ui_canvas);
void						copy_canvas_to_temp(t_list *canvas_list);
void						copy_temp_to_screen(t_list *canvas_list,
								t_img_data *img);
void						copy_temp_to_canvas(t_list *canvas_list);
t_point2i					screen_to_canvas(t_point2i screen_point,
								t_canvas *canvas);

/*############################################################################*/
/*                              GAME STATE                                    */
/*############################################################################*/

t_setup_by_game_state		*initialize_canvas_setups(void);
int							initialize_setup_by_state(
								t_setup_by_game_state *setup,
								t_modus_state state);
int							initialize_map_editor_setup(
								t_setup_by_game_state *setup);
int							initialize_gameplay_setup(
								t_setup_by_game_state *setup);
int							initialize_menu_setup(
								t_setup_by_game_state *setup);
size_t						get_init_table_size(t_canvas_init_entry *table);
/*############################################################################*/
/*                              FUSING CANVASES                               */
/*############################################################################*/

int							merge_canvases(t_list **canvas_list);
int							merge_canvas(t_canvas *final_canvas,
								t_canvas *canvas);

void						reorder_canvases_by_z_index(t_list **canvas_list);
bool						should_swap(t_canvas *a, t_canvas *b);
void						swap_canvas_content(t_list *a, t_list *b);

/*############################################################################*/
/*                              MLX CONVERSION                                */
/*############################################################################*/

void						canvas_to_mlx_image(t_img_data screen,
								t_canvas *final_canvas);

/*############################################################################*/
/*                              DRAW FUNCTIONS                                */
/*############################################################################*/

void						img_pix_put(t_img_data *img, int x, int y,
								int color);

int							put_pixel_transparent(t_color *dest, t_color *src);

void						draw_segment(
								t_img_data *img,
								t_segment_d const *const segment,
								int color
								);
void						draw_one_line(
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
void		draw_segment_canvas(
				t_canvas *canvas,
				t_segment_d const *const segment,
				t_color color
				);
void		fill_canvas(
				t_canvas *canvas,
				t_color color
				);

/*############################################################################*/
/*                              ALIGNMENT METHODS                             */
/*############################################################################*/
void						*aligned_malloc(size_t size, size_t alignment);
void						aligned_free(void *ptr);
void						*aligned_calloc(size_t nmemb,
								size_t size,
								size_t alignment);

/*############################################################################*/
/*                              ALIGNMENT METHODS                             */
/*############################################################################*/
int							map_visualizer_draw(t_cub *data);
void						redraw_scene(t_cub *data, t_canvas *canvas);

/*############################################################################*/
/*                              UTILS FOR LIFE                                */
/*############################################################################*/
bool						is_valid_canvas(t_canvas *canvas);
#endif
