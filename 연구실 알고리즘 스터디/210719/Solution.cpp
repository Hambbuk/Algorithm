#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAX_N 1000
#define MAX_M 20

struct Result {
	int y, x;
};

void init(int N, int M, int Map[MAX_N][MAX_N])
{
	printf("===============================MAP==========================================\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ",Map[i][j]);
		}
		printf("\n");
	}
	printf("============================================================================\n");
}

Result findConstellation(int stars[MAX_M][MAX_M])
{
	Result res;

	res.y = res.x = 0;
	return res;
}