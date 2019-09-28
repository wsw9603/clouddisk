/*
 * 堆排序 * 小/大顶堆 *
 * 将数组看成一棵完全二叉树，下标为i的节点的左右孩子节点分别为2i+1和2i+2，
 * 如果树的每个节点都不超过左右孩子节点，则这棵树即为一个小顶堆，根节点的
 * 值为所有元素的最小值；对于数组，i=0的节点即为根节点。
 *
 * 将一棵完全二叉树调整成一个小顶堆，从最后一个非叶子节点元素开始往前调整
 * 对每个非叶子节点，如果当前非节点的值大于某个孩子的值，则与最小的孩子交
 * 换并且继续调整该孩子子节点，直到该节点大于等于两个孩子节点的值，或者该
 * 节点是叶子节点。
 *
 * 堆的删除和插入元素
 * 插入元素放到最后，从后向前调整；
 * 删除元素，删除堆顶元素，并把最后一个元素放到堆顶，然后从堆顶开始调整。
 *
 * 非降序排列，构造大顶堆，将堆顶元素放到最后。
 */

#include <sort.h>
#include "common.h"

/*
 * 将长度为length的数组array，以parent为root的子树调整成一个大顶堆
 */
static void heap_adjest(int array[], int length, int parent)
{
	while (parent <= length / 2 - 1) {
		int lchild = 2 * parent + 1;
		int rchild = 2 * parent + 2;
		int max = parent;
		max = array[max] < array[lchild] ? lchild : max;
		if (rchild < length)
			max = array[max] < array[rchild] ? rchild : max;
		if (max == parent)
			break;
		swap(array + parent, array + max);
		parent = max;
	}
}

void heap_sort(int array[], int length)
{
	int i;
	for (i = length / 2 - 1; i >= 0; i--)
		heap_adjest(array, length, i);

	for (i = length - 1; i > 0; i--) {
		swap(array, array + i);
		heap_adjest(array, i, 0);
	}
}
