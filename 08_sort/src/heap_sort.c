/*
 * 堆排序 * 小/大顶堆 *
 * 将数组看成一棵完全二叉树，下标为i的节点的左右孩子节点分别为2i+1和2i+2，
 * 如果树的每个节点都不超过左右孩子节点，则这棵树即为一个小顶堆，根节点的
 * 值为所有元素的最小值；对于数组，i=0的节点即为根节点。
 *
 * 将一棵完全二叉树调整成一个小顶堆，从最后一个非叶子节点元素开始，如果该
 * 节点的值大于叶子节点的值，则交换。
 *
 * 非降序排列，构造大顶堆，将堆顶元素放到最后。
 * 本质上只是用“堆”这个概念比较快速的寻找数组中的最小/大值而已，跟选择排序
 * 类似。
 */

#include <sort.h>
#include "common.h"

/*
 * 将长度为length的数组array调整成一个小顶堆
 */
static void heap_adjest(int array[], int length)
{
	int i, min, l, r;
	for (i = length / 2 - 1; i >= 0; i--) {
		min = i;
		l = 2 * i + 1;	//l 一定会小于length
		r = 2 * i + 2;
		min = array[min] < array[l] ? min : l;
		if (r < length)
			min = array[min] < array[r] ? min : r;
		if (min != i)
			swap(array + i, array + min);
	}
}

void heap_sort(int array[], int length)
{
	while (length > 1)
		heap_adjest(array++, length--);
}
