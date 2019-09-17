/*
 * 各种排序算法，以及性能比较
 */

#include <stdio.h>
#include <sort.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define OK 0
#define FAILED -1

#define ARRAY_SIZE 100000
#define MAX_NUM    20000

void init()
{
	srand((unsigned)time(NULL));
}

void print_array(int array[], int length)
{
	if (length > 100)
		return;
	int i;
	for (i = 0; i < length; i++) {
		printf("%5d", array[i]);
		if ((i + 1) % 8 == 0)
			printf("\n");
	}
	printf("\n");
}


#define EXIT   0
#define BUDDLE 1
#define HEAP   2

/*
 * 打印菜单并获取用户输入，成功返回0，失败返回-1
 */
int print_menu(int *menu, int *length, int *max)
{
	printf("*************************************************************\n");
#define MENU(m, str) printf("%d. %s\n", m, #str)
	MENU(EXIT, exit);
	MENU(BUDDLE, buddle);
	MENU(HEAP, heap);
#undef MENU
	printf("please select a menu and set array size and max element value\n");

	scanf("%d", menu);
	if (*menu == EXIT)
		return OK;

	scanf("%d %d", length, max);

	return OK;
}

/*
 * 返回长度为length，最大值小于max的int数组，数组内存为动态申请的
 */
int *generate_arry(int length, int max)
{
	int *array = malloc(length * sizeof(int));
	if (array == NULL) {
		printf("alloc memory failed\n");
		return NULL;
	}

	int i;
	for (i = 0; i < length; i++)
		array[i] = rand() % max;
	return array;
}

void print_time(struct timeval *start, struct timeval *end)
{
	long ss = start->tv_sec;
	long su = start->tv_usec;
	long es = end->tv_sec;
	long eu = end->tv_usec;
	long carry = eu < su ? 1 : 0;

	printf("process start at %ld sec, %ld usec\n", ss, su);
	printf("process end at %ld sec, %ld usec\n", es, eu);
	printf("duration %ld sec, %ld usec", es - ss - carry, carry * 1000000 + eu - su);
}

void fun()
{
	int menu, length, max;
	int *array = NULL;
	struct timeval start_time, end_time;

	while (1) {
		if (FAILED == print_menu(&menu, &length, &max)) {
			continue;
		}

		if (menu == EXIT) {
			return;
		}

		array = generate_arry(length, max);
		if (array == NULL) {
			continue;
		}

		printf("origin array\n");
		print_array(array, length);
		gettimeofday(&start_time, NULL);
		switch (menu) {
			case BUDDLE: buddle_sort(array, length);
				     break;
			case HEAP: heap_sort(array, length);
				   break;
		}
		gettimeofday(&end_time, NULL);

		printf("after sort\n");
		print_array(array, length);

		print_time(&start_time, &end_time);
		free(array);
	}
}

int main()
{
	init();
	fun();

	return 0;
}
