/*
 * 归并排序
 * 升序排列
 * 空间复杂度O(n)
 * 使用非递归方式实现
 */

#include <sort.h>
#include <stdlib.h>
#include "common.h"

/*
 * 将两个有序数组合并成一个有序数组，放在des开始的数组里
 * 两个有序数组分别为src[0]~src[mid-1]和src[mid]~src[end-1]
 */
static void merge(int des[], int src[], int mid, int end)
{
	int i = 0, j = 0, k = 0;
	int *s1 = &src[0];
	int *s2 = &src[mid];
	int len1 = mid;
	int len2 = end - mid;

	while (k < end) {
		while  (i < len1 && (j == len2 || s1[i] <= s2[j]))
			des[k++] = s1[i++];
		while  (j < len2 && (i == len1 || s2[j] < s1[i]))
			des[k++] = s2[j++];
	}
}

void merge_sort(int array[], int length)
{
	int *arr = malloc(sizeof(int) * length);
	if (!arr)
		return;

	int step = 1;
	while (step < length) {
		int i;
		for (i = 0; i < length; i += step * 2) {
			int tail = length - i;
			if (tail > step * 2)
				merge(&arr[i], &array[i], step, step * 2);
			else if (tail > step)
				merge(&arr[i], &array[i], step, tail);
			else
				merge(&arr[i], &array[i], tail, tail);
		}
		step *= 2;
		for (i = 0; i < length; i += step * 2) {
			int tail = length - i;
			if (tail > step * 2)
				merge(&array[i], &arr[i], step, step * 2);
			else if (tail > step)
				merge(&array[i], &arr[i], step, tail);
			else
				merge(&array[i], &arr[i], tail, tail);
		}
		step *= 2;
	}
	free(arr);
}
