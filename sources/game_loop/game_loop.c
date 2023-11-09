
#include "game_loop.h"

void	game_update(t_cub *data)
{
	player_handle_event(data);
}

int	game_loop(t_cub *data)
{
	if (data->win_ptr == NULL)
		return (1);
	game_update(data);
	game_render(data);
	usleep(30000);
	return (0);
}
