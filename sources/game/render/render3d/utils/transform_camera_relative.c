#include "structures.h"

t_vector4d	transform_camera_relative_point(t_vector4d point, t_camera *camera)
{
	t_vector4d	relative_point;
	// double		old_z;

	// old_z = point.z;
	point.vec = point.vec - camera->pos.vec;
	relative_point.x = point.x * camera->dir.y - point.y * camera->dir.x;
	relative_point.y = point.x * camera->dir.x + point.y * camera->dir.y;
	relative_point.z = point.z;
	relative_point.w = point.w;
	return (relative_point);
}

t_segment_d	transform_camera_relative_segment(
	t_segment_d segment,
	t_camera *camera)
{
	segment.point_a = transform_camera_relative_point(segment.point_a, camera);
	segment.point_b = transform_camera_relative_point(segment.point_b, camera);
	return (segment);
}
