#ifndef __COMMON_H__
#define __COMMON_H__

#define MAX_INT 0x7FFFFFFF

void inline swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

#endif
