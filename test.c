#include <sys/time.h>
#include <stdio.h>

int main()
{
	struct timeval l;
	gettimeofday(&l, NULL);
	printf("It Is : %d\n", l);
}