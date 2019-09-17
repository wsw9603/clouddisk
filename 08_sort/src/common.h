#ifndef __COMMON_H__
#define __COMMON_H__

void inline swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

#endif
