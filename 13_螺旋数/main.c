/*
 * 7 8 9 10
 * 6 1 2 11
 * 5 4 3 12
 *
 * 观察以上数字，1 为坐标远点的位置(0, 0)，x轴向右增长，y轴向下增长，
 * 给出坐标(x, y)输出该点的数字的值。
 *
 * 分析：
 * 观察可以发现(n, -n)点的值是(2n+1)^2，接下来点的变化分四步:
 * 1. (n+1, -n) (n+1, -n+1) y增大一直到(n+1, n+1)
 * 2. (n, n+1)   x减小一直到(-n-1, n+1)
 * 3. (-n-1, n)  y减小一直到(-n-1, -n-1)
 * 4. (-n, -n-1) x增大一直到(n+1, -n-1)
 * 以上4步每步都有2n+2个点
 *
 * 对于点(x, y)
 * n = max(|x|, |y|) - 1
 */

#include <stdio.h>

#define my_abs(x)	((x) > 0 ? (x) : -(x))
#define my_max(a, b)	((a) > (b) ? (a) : (b))

int fun(int x, int y)
{
	if (x == 0 && y == 0)
		return 1;
	int n = my_max(my_abs(x), my_abs(y)) - 1;
	int base = (2 * n + 1) * (2 * n + 1);

	if (x == n + 1 && y >= -n)
		return base + y + n + 1;
	base += 2 * n + 2;
	if (y == n + 1)
		return base + n + 1 - x;
	base += 2 * n + 2;
	if (x == -(n + 1))
		return base + n + 1 - y;
	base += 2 * n + 2;
	return base + x + n + 1;
}

int main()
{
	int x, y;
	scanf("%d %d", &x, &y);
	printf("number on pos (%d, %d) is: %d\n", x, y, fun(x, y));

	return 0;
}
