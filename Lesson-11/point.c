#include <stdio.h>
#include <math.h>

struct point
{
	float x;	// x axis
	float y;	// y axis
	int test[100];
};

//#define struct point point_t
typedef struct point point_t;

float calculate(point_t p, point_t p2)
{
	float dx, dy;

	printf("<debug 2> &p = %p\n", &p);
	printf("<debug 2> p.x = %.1f, p.y = %.2f\n", p.x, p.y);

	dx = p.x - p2.x;
	dy = p.y - p2.y;

	return sqrt(dx * dx + dy * dy);
}

int main(void)
{
	float x, y;
	point_t p;
	point_t p2 = {1.5, 2.5};
	float distance;
	struct point test;

	printf("demo structure\n");
//	p = {1.0, 2.0};
	//p.x = 1.0;
	//p.y = 2.0;
	//p = p2;
	scanf("%f %f", &p.x, &p.y);

	printf("p.x = %.1f, p.y = %.2f\n", p.x, p.y);

	printf("<debug> &p = %p\n", &p);
	distance = calculate(p, p2);
	printf("distance = %f\n", distance);
#if 0
	printf(" sizeof float = %d\n", sizeof(float));
	printf(" sizeof double = %d\n", sizeof(double));
	printf(" sizeof char = %d\n", sizeof(char));
	printf(" sizeof int = %d\n", sizeof(int));
	printf(" sizeof struct point = %d\n", sizeof(struct point));
#endif

	return 0;
}
