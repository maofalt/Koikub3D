
#include "draw_utils.h"
#include "structures.h"
#include "render_3D.h"

t_vector4d project_point(t_3d_render *render, t_vector4d point)
{
	t_vector4d transformed_point;

	int xscale = 512 / (render->scale_factor_x / 1.2);
	int yscale = 32 / (render->scale_factor_y / 1.2);



	transformed_point.x = -point.x * xscale / point.y;
	transformed_point.y = point.z * yscale / point.y;
	transformed_point.z = point.y;
	transformed_point.w = 0;
	// transformed_point.vec *= 16;
	transformed_point.vec += render->middle.vec;
	return (transformed_point);
}


int	project_segment(
	t_3d_render *render,
	t_segment_d segment,
	t_segment_d *projected_seg)
{
	segment = transform_camera_relative_segment(segment, render->camera);
	if (relative_segment_clip_front(&segment))
		return (1);
	segment.point_a = project_point(render, segment.point_a);
	segment.point_b = project_point(render, segment.point_b);
	if (segment.point_a.x < segment.point_b.x)
	{
		*projected_seg = segment;
	}
	else
	{
		projected_seg->point_a = segment.point_b;
		projected_seg->point_b = segment.point_a;
	}
	return (0);
}


int project_wall(t_3d_render *render,
					t_segment_d *wall,
					t_segment_d *projected_top,
					t_segment_d *projected_bottom
					)
{
	wall->point_a.z = wall->data.floor;
	wall->point_b.z = wall->data.floor;
	if (project_segment(render, *wall, projected_bottom))
		return (1);
	wall->point_a.z = wall->data.ceil;
	wall->point_b.z = wall->data.ceil;
	if (project_segment(render, *wall, projected_top))
		return (1);
	if (projected_bottom->point_a.x == projected_bottom->point_b.x)
		return (1);
	return (0);
}
