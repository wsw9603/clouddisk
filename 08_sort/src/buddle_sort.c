#include <sort.h>
#include "common.h"

void buddle_sort(int array[], int length)
{
	int flag = 1, i, j;
	for (i = 1; i < length && flag == 1; i++) {
		flag = 0;
		for (j = i; j < length; j++) {
			if (array[j-1] > array[j]) {
				swap(array + j - 1, array + j);
				flag = 1;
			}
		}
	}
}
