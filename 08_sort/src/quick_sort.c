/*
 * 快速排序
 * 类似于冒泡排序，极端情况下会退化成冒泡排序
 * 原理，选取基准值a，将小于等于a的放在左边，大于a的放在右边
 * 对左边和右边分别选取基准值重复操作
 * 基准值的选取有多种方式，代码中选择第一个元素为基准元素
 */

#include <sort.h>
#include "common.h"

void quick_sort(int array[], int length)
{
	int temp = array[0];
	int low = 0;
	int high = length - 1;

	while (low < high) {
		while (high > low && array[high] > temp)
			high--;
		if (high == low) {
			array[high] = temp;
			break;
		}
		array[low++] = array[high];

		while(high > low && array[low] <= temp)
			low++;
		if (high == low) {
			break;
		}
		array[high--] = array[low];
	}
	array[high] = temp;

	if (low > 1)
		quick_sort(array, low);
	if (++low < length)
		quick_sort(&array[low], length - low);
}
