/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:24:57 by motero            #+#    #+#             */
/*   Updated: 2023/10/14 19:21:52 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdint.h>
# include <stdio.h>
# include "libft.h"
# include "../gnl/get_next_line.h"
# include "colors.h"
# include "mlx_int.h"

/*############################################################################*/
/*                              STRUCTURES                                    */
/*############################################################################*/

/* Vector structure for 2D float vector
** Vector structure for 2D unsigned int vector
** Vector structure for 2D int vectors
** causes the compiler to set the mode for foo,
** to be 16 bytes, divided into int sized units.
** SIMD vectorrization
** https://users.ece.cmu.edu/~franzf/teaching/slides-18-645-simd.pdf
**
*/

typedef float			t_vector_f		__attribute__((vector_size (8)));
typedef unsigned int	t_vector_u		__attribute__((vector_size (8)));
typedef int				t_vector_i		__attribute__((vector_size (8)));

typedef int				t_v2i			__attribute__((vector_size (2
	* sizeof(int))));
typedef double			t_v2d			__attribute__((vector_size (2
	* sizeof(double))));
typedef u_int8_t		t_vector_color	__attribute__((vector_size (4
	* sizeof(u_int8_t))));
typedef double			t_v4d			__attribute__((vector_size (4
	* sizeof(double))));

/* bpp = bits per pixel */
typedef struct s_img_data
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	t_vector_i	size;
}	t_img_data;

/*############################################################################*/
/*                              	ASSETS                                    */
/*############################################################################*/

typedef enum e_ui_assets
{
	WINDOW_BASE,
	WINDOW_HEADER_INACTIVE,
	WINDOW_HEADER_RESIZABLE_INACTIVE,
	WINDOW_HEADER_RESIZABLE,
	WINDOW_HEADER,
	WINDOWS_BUTTON_FOCUS_OUTLINED,
	WINDOWS_BUTTON_FOCUS,
	WINDOWS_BUTTON_INACTIVE,
	WINDOWS_BUTTON_PRESSED_OUTLINED,
	WINDOWS_BUTTON_PRESSED,
	WINDOWS_BUTTON,
	WINDOWS_DIVIDER_LINE,
	WINDOWS_EXAMPLE_ITCHPIC,
	WINDOWS_EXAMPLE_MAIN,
	WINDOWS_EXAMPLE_POPUP,
	WINDOWS_ICONS,
	WINDOWS_INNER_FRAME_INVERTED,
	WINDOWS_INNER_FRAME,
	WINDOWS_PROGRESS_FILL,
	WINDOWS_RATIO_INACTIVE,
	WINDOWS_RATIO_SELECTED,
	WINDOWS_RATIO,
	WINDOWS_SIDEBAR_UNDERSIDE,
	WINDOWS_SLIDER_BACKGROUND,
	WINDOWS_SLIDER_HANDLE,
	WINDOWS_TOGGLE_ACTIVE,
	WINDOWS_TOGGLE_INACTIVE,
	WINDOWS_TOGGLE_SELECTED,
	BACKGROUND,
	ICON_DRAW,
	ICON_GAME,
	BAR_WITH_DRAW,
	SIDE_BAR,
	ASSET_COUNT
}	t_ui_assets;

/* Parsing structure for CUB3D stocking information from .cub file
** a wolrd map in a 2D int array of MAPWIDTH * MAPHEIGHT
** a array  of size 4 of sprites using t_image from the mlx
** in the order from indx 0 to 3 : N, S, E, W
** a uint_32_t for the color of the floor
** a uint_32_t for the color of the ceiling
*/

typedef union u_color
{
	t_vector_color	rgb_color;
	u_int32_t		d;
	struct
	{
		u_int8_t	a;
		u_int8_t	r;
		u_int8_t	g;
		u_int8_t	b;
	};
}	t_color;

typedef struct s_player
{
	t_vector_f	pos;
	t_vector_f	dir;
	t_vector_f	plane;
}				t_player;

typedef struct s_dda
{
	t_vector_f	ray_dir;
	t_vector_f	side_dist;
	t_vector_f	delta_dist;
	t_vector_i	map;
	t_vector_f	pos;
	t_vector_i	step;
	uint32_t	color;
	float		perp_wall_dist;
	float		tex_pos;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			hit;
	int			side;
	int			tex_y;
	int			x;
	t_vector_i	mouse;
}				t_dda;

typedef enum e_drawing_state
{
	NOT_DRAWING,
	DRAWING,
	END_DRAWING
}	t_drawing_state;

typedef enum e_update_type
{
	UPDATE = 0,
	FULL_REDRAW = 1,
	LINE_REDRAW = 2,
	NO_UPDATE = 4
}	t_update_type;

typedef enum e_modus_state
{
	MENU,
	MAP_EDITOR,
	GAMEPLAY,
	END_GAME_STATE
}	t_modus_state;

typedef enum e_img_fit_mode
{
	FIT_IMAGE_TO_CANVAS,
	FIT_CANVAS_TO_IMAGE
}	t_img_fit_mode;


typedef struct s_data
{
	char		**textures;
	char		**colors;
	char		***map;
}				t_data;

typedef union u_point2i
{
	t_v2i	vec;
	struct {
		int	x;
		int	y;
	};
}	t_point2i;

typedef union u_point2d
{
	t_v2d	vec;
	struct {
		double	x;
		double	y;
	};
}	t_point2d;

typedef union u_vector4d
{
	t_v4d	vec;
	struct {
		double	x;
		double	y;
		double	z;
		double	w;
	};
}	t_vector4d;

typedef enum e_segment_type
{
	WALL,
	PORTAL
}	t_segment_type;

typedef struct s_wall_data
{
	int		size;
	double	height;
	double	floor_height;	
}	t_wall_data;

typedef struct s_portal_data
{
	int		size;
	int		id;
	int		*destinations_id;
	void	*destination;
}	t_portal_data;

typedef union u_wall_portal_data
{
	t_wall_data		wall;
	t_portal_data	portal;	
}	t_wall_portal_data;

typedef union s_segment_data
{
	t_segment_type		type;
	t_wall_portal_data	data;
}	t_segment_data;

typedef struct s_segment_i
{
	t_point2i		point_a;
	t_point2i		point_b;
	t_segment_data	data;
}	t_segment_i;

typedef struct s_segment_d
{
	t_vector4d		point_a;
	t_vector4d		point_b;
	t_segment_data	data;
}	t_segment_d;

typedef enum e_direction{
	NONE = 0,
	RIGHT = 1,
	DOWN = 2,
	DIAGONAL_RIGHT = 4,
	DIAGONAL_LEFT = 8
}	t_direction;

typedef struct s_edge_exploration_context{
	t_vector4d		coord;
	t_vector4d		delta;
	t_vector4d		current_coord;
	t_segment_d		segment;
	char			**map;
	t_direction		direction;
	t_direction		**visited;
}	t_edge_exploration_context;

typedef struct s_tree_node
{
	struct s_tree_node	*left;
	struct s_tree_node	*right;
	void				*data;
}	t_tree_node;


typedef struct s_cub
{
	t_img_data				texture[4];
	t_img_data				screen;
	t_img_data				ui_images[ASSET_COUNT];
	uint32_t				floor;
	uint32_t				celling;
	t_point2i				mouse_pos;
	t_player				player;
	t_dda					dda;
	size_t					mapwidth;
	size_t					mapheight;
	t_img					img;
	void					*mlx_ptr;
	void					*win_ptr;
	char					**map;
	t_drawing_state			drawing;
	t_update_type			update;
	t_modus_state			*game_states;
	t_modus_state			game_state;
	t_list					*canvas_list;
	void					*active_canvas;
	void					*setup_canvas;
	t_list					*segments_list;
}				t_cub;

typedef struct s_event_handlers {
	int	(*on_keypress)(int keysym, void *self, t_cub *data);
	int	(*on_boutonpress)(int keysym, t_point2i mouse_pos,
			void *self, t_cub *data);
	int	(*on_mousemove)(t_point2i mouse_pos, void *self, t_cub *data);
	int	(*render)(void *self, t_cub *data);
}	t_event_handlers;

typedef int				(*t_canvas_func)(void *, t_cub *);


#endif
