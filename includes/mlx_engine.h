/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_engine.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:41:27 by motero            #+#    #+#             */
/*   Updated: 2023/10/16 17:46:11 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_ENGINE_H
# define MLX_ENGINE_H

# include "cub3D.h"
# include "mlx.h"
# include "structures.h"

/*############################################################################*/
/*                              BUTTONS DEFINITION                            */
/*############################################################################*/

# define UP_KEY 65362
# define DOWN_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define MINUS_PAD 65453
# define PLUS_PAD 65451
# define ONE_PAD 65436
# define TWO_PAD 65433
# define THREE_PAD 65435
# define FOUR_PAD 65430
# define FIVE_PAD 65437
# define SIX_PAD 65432
# define MINUS_KEY 45
# define PLUS_KEY 61
# define BRACE_L_KEY 91
# define BRACE_R_KEY 93
// # define D_KEY 100
// # define C_KEY 99
// # define Z_KEY 122
// # define Q_KEY 113
// # define S_KEY 115
// # define A_KEY 97
// # define W_KEY 119

typedef struct s_key_action_map
{
	int				key_id;
	enum e_action	action;
}	t_key_action_map;

static const t_key_action_map	g_key_to_action[] = {
{XK_w, a_move_up},
{XK_s, a_move_down},
{XK_a, a_move_left},
{XK_d, a_move_right},
{-1, -1},
};

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

# ifndef FOV
#  define FOV 90
# endif

/*############################################################################*/
/*                              MLX_ENGINE FUNCTIONS                          */
/*############################################################################*/

int		ft_mlx_initialize_pointers(t_cub *data);
int		ft_mlx_create_window_and_image(t_cub *data);

/*############################################################################*/
/*                              MLX_ENGINE HOOKS                          */
/*############################################################################*/

void	ft_mlx_engine(t_cub *data);
int     ft_destroy_window(t_cub *data);
int	    ft_handle_keyrelease(int keysym, t_cub *data);
int     ft_handle_keypress(int keysym, t_cub *data);
int     ft_handle_boutonpress(int buttonsym, int x, int y, t_cub *data);


/*############################################################################*/
/*                              KEYPRESS EVENTS                               */
/*############################################################################*/
void	ft_destroy_window_button(int keysym, t_cub *data);
void	ft_movements_keys(int keysym, t_cub *data, int state);

#endif
