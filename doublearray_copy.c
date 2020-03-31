// https://inhwascope.tistory.com/117

#include <stdio.h>
#define HEIGHT 5
#define WIDTH 10
void print(int array[][WIDTH]);
void copy(int array1[][WIDTH], int array2[][WIDTH]);
int main(void)
{
	int image1[HEIGHT][WIDTH] = { {0,0,0,0,9,0,0,0,0,0},
	{1,0,0,9,9,0,0,0,0,0},
	{5,0,9,0,9,0,0,0,0,4},
	{4,0,0,0,8,0,0,2,0,0},
	{3,0,0,0,9,0,0,0,0,8} };
	int image2[HEIGHT][WIDTH] = { {0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0} };
	printf("이미지1 : \n");
	print(image1);
	printf("이미지2 : \n");
	print(image2);
	copy(image1, image2);
	printf("복사된이미지2 : \n");
	print(image2);
	return 0;
}
void print(int array[][WIDTH])
{
	int i, j;
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			printf("%3d ", array[i][j]);
		}
		printf("\n");
	}
}
void copy(int array1[][WIDTH], int array2[][WIDTH])
{
	int *p1, *endp1;
	int *p2;
	p1 = &array1[0][0];
	p2 = &array2[0][0];
	endp1 = &array1[HEIGHT - 1][WIDTH - 1];
	while (p1 <= endp1)
	{
		*p2 = *p1;
		p1++; p2++;
	}
}