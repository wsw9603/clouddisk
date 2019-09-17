/*
 * 输入
 * 第一行输入数字n，表示广场上有n个人，(0 < n <= 200 000)
 * 第二行输入n个整数，表示n个人身上的数字，(0 <= m <= 100 000)
 * 输出
 * 单身的人数，即出现了一次的数字的个数
 *
 * 示例
 * 输入
 * 5
 * 1 1 2 2 3
 * 输出
 * 1
 *
 * 考虑到某单身狗身上的数字可能跟某对情侣相同，所以应该是输出出现了奇数次的数字的个数
 */

#include <stdio.h>

typedef unsigned long map_element_t;

#define MAX_NUM     100000
#define ELEMENT_LEN (sizeof(map_element_t) * 8)

map_element_t bitmap[MAX_NUM/ELEMENT_LEN + 1] = {0};
int n;

/* 返回ele的二进制表示中1的个数 */
int get_ones(map_element_t ele)
{
	int i = 0;
	while (ele != 0) {
		ele &= ele - 1UL;
		i++;
	}
	return i;
}

int main()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		int num;
		scanf("%d", &num);
		bitmap[num / ELEMENT_LEN] ^= 1UL << (num % ELEMENT_LEN);
	}

	int result = 0;
	for (i = 0; i < MAX_NUM/ELEMENT_LEN; i++)
		result += get_ones(bitmap[i]);
	result += get_ones(bitmap[i] & ((1UL << MAX_NUM % ELEMENT_LEN + 1) - 1));

	printf("%d", result);

	return 0;
}
