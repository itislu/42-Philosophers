#include <sys/time.h>
#include <stdio.h>
#include <string.h>

// I want to find out what happens if timersub can result in a negative timeval.

int	main(void)
{
	struct timeval	tv1;
	struct timeval	tv2;
	struct timeval	result;

	tv1.tv_sec = 0;
	tv1.tv_usec = 0;
	tv2.tv_sec = 0;
	tv2.tv_usec = 300000;
	timersub(&tv1, &tv2, &result);

	if (!timercmp(&result, (&(struct timeval){0, 0}), >))
		timersub((&(struct timeval){0, 0}), &result, &result);

	printf("result.tv_sec: %ld\n", result.tv_sec);
	printf("result.tv_usec: %ld\n", result.tv_usec);

	return (0);
}