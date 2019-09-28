/*
 * 选择排序，选择出无序部分的最小值，放到有序序列的尾部
 */
#include <sort.h>
#include "common.h"

void select_sort(int array[], int length)
{
	int i, j;
	for (i = 0; i < length-1; i++) {
		int min_idx = i;
		for (j = i+1; j < length; j++)
			if (array[min_idx] > array[j])
				min_idx = j;
		if (min_idx != i)
			swap(array + min_idx, array + i);
	}
}
