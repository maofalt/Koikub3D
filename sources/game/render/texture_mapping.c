

#include "structures.h"
#include "ressources_managers.h"

double	calc_seg_coef(
			t_segment_d *segment
			);

int project_wall(t_3d_render *render,
					t_segment_d *wall,
					t_segment_d *projected_top,
					t_segment_d *projected_bottom
					);

static inline void	draw_vertical_line(
			t_canvas *canvas,
			t_img_data	*image,
			int 	img_x,
			int 		screen_x,
			int 		screen_top,
			const int	screen_bottom
			)
{
	uint32_t	*img = (void *)image->addr;
	int			offset;
	int			offset_img;
	double		y = 0;

	img_x = img_x % image->size.x;
	double factor  =  (double)image->size.y / (double) (screen_bottom - screen_top);
	y = fmax(-screen_top, y);
	while (screen_top + y < screen_bottom)
	// while (y * factor < image->size.y)
	{
		if (y + screen_top >= canvas->size.y)
			return;
		if (img_x > canvas->size.x)
			return;
		// if (y + screen_top < 0)
		// 	return;
		offset = (screen_top + y) * canvas->size.x + screen_x;
		offset_img = (((int)(factor * y) % image->size.y) * image->size.x) + img_x;
		canvas->pixels[offset].d = img[offset_img];
		++y;
	}
}


void	draw_wall_texture(
		t_3d_render *render,
		t_segment_d	*wall,
		double left,
		double right
	)
{
	t_segment_d		projected_top;
	t_segment_d		projected_bot;
	double			coef_top;
	double			coef_bot;

	if (project_wall(render, wall, &projected_top, &projected_bot))
		return ;
	left = fmax(projected_top.point_a.x, left);
	right = fmin(projected_top.point_b.x, right);
	coef_bot = calc_seg_coef(&projected_bot);
	coef_top = calc_seg_coef(&projected_top);
	projected_top.point_a.y += coef_top * (left - projected_top.point_a.x);
	projected_top.point_b.y += coef_top * (right - projected_top.point_b.x);
	projected_bot.point_a.y += coef_bot * (left - projected_bot.point_a.x);
	projected_bot.point_b.y += coef_bot * (right - projected_bot.point_b.x);
	double x = 0;

	// double wall_size = (right - left);

	// wall_size = fmin(texture_get_frame(wall->data.data.wall.texture.texture)->size.x, wall_size);

	// wall_size = (double)((int)wall_size % (int)texture_get_frame(wall->data.data.wall.texture.texture)->size.x);
	// sqrt(
	// pow(((double)wall->point_a.x - (double)wall->point_b.x), 2)+
	// pow(((double)wall->point_a.y - (double)wall->point_b.y), 2));
	double factor  =  texture_get_frame(wall->data.data.wall.texture.texture)->size.y / fmin((projected_bot.point_a.y - projected_top.point_a.y), (projected_bot.point_b.y - projected_top.point_b.y));
	// factor = fmax(factor, 1);
	// factor /;
	printf("factors :%f, bot:%f, top:%f \n", factor, projected_bot.point_a.y, projected_top.point_a.y);
	while (left + x < right)
	{
		// draw_solid_wall_line(render->canvas, x, projected_top.point_a.y,
		// 	projected_bot.point_a.y);
		draw_vertical_line(render->canvas,
			texture_get_frame(wall->data.data.wall.texture.texture), x * factor,
				left + x ,projected_top.point_a.y, projected_bot.point_a.y);

		projected_top.point_a.y += coef_top;
		projected_bot.point_a.y += coef_bot;
		++x;
	}

}
// 		draw_vertical_line(canvas, image, x, 500, 90+ x/10, 200 - x/10);


// void	draw_solid_wall(
// 	t_3d_render *render,
// 	t_segment_d	*wall,
// 	double left,
// 	double right
// 	)
// {
// 	t_segment_d		projected_top;
// 	t_segment_d		projected_bot;
// 	double			coef_top;
// 	double			coef_bot;

// 	if (project_wall(render, wall, &projected_top, &projected_bot))
// 		return ;
// 	left = fmax(projected_top.point_a.x, left);
// 	right = fmin(projected_top.point_b.x, right);
// 	coef_bot = calc_seg_coef(&projected_bot);
// 	coef_top = calc_seg_coef(&projected_top);
// 	projected_top.point_a.y += coef_top * (left - projected_top.point_a.x);
// 	projected_top.point_b.y += coef_top * (right - projected_top.point_b.x);
// 	projected_bot.point_a.y += coef_bot * (left - projected_bot.point_a.x);
// 	projected_bot.point_b.y += coef_bot * (right - projected_bot.point_b.x);
// 	double x;
// 	while (x + left < right)
// 	{
// 		draw_solid_wall_line(render, left, , projected_top.point_a.y,
// 			projected_bot.point_a.y);
// 		projected_top.point_a.y += coef_top;
// 		projected_bot.point_a.y += coef_bot;
// 		++x;
// 	}
// }
