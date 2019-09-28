#include <sort.h>

/*
 * 插入排序，将一个数插入到一个有序序列中
 */

void insert_sort(int array[], int length)
{
	int i, j;
	for (i = 0; i < length-1; i++) {
		int temp = array[i+1];
		for (j = i; j >= 0 && temp < array[j]; j--)
			array[j+1] = array[j];
		array[j+1] = temp;
	}
}
