#include <stdio.h>
#include <time.h>

long get_nanos()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (long)ts.tv_sec * 1000000000L + ts.tv_nsec;
}

void count_fps()
{
	static int	frame_count = 0;
	static long	last_frame_time = 0;
	const long	current_time = get_nanos();

	++frame_count;
	if (current_time - last_frame_time >= 1000000000L)
	{
		printf("FPS: %d\n", frame_count);
		frame_count = 0;
		last_frame_time = current_time;
	}
}
