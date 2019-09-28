/*
 * 希尔排序
 * 插入排序的改进版，开始时选取较长的步长来排序
 */

#include <sort.h>

/*
 * 对数组array从start开始的位置进行步长为step的排序
 */
static void sort_on_step(int array[], int step, int length, int start)
{
	int i, j;
	for (i = start; i < length - step; i += step) {
		int temp = array[i + step];
		for (j = i; j >= start && temp < array[j]; j -= step)
			array[j+step] = array[j];
		array[j+step] = temp;
	}
}

void shell_sort(int array[], int length)
{
	int step;
	for (step = length/2; step > 0; step /= 2) {
		int i, j, start;
		for (start = 0; start < step; start++)
			sort_on_step(array, step, length, start);
	}
}
