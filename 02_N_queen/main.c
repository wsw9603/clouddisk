/*
 * N皇后问题
 * 方法：回溯，递归
 *
 * options 记录N皇后问题的可能解答数目
 * raw_status[i] 记录当前到棋盘第i行的路径，或者棋盘第i行的皇后放置的位置，i=0,1,2...
 */

#include <stdio.h>

static int N = 8;

static int options = 0;
static int raw_status[15];

/*
 * 根据raw_status数组的前raw-1行，判断棋盘第raw行的，第pos个位置是否可以放置皇后
 */
int is_ok(int raw, int pos)
{
	int i;
	for (i = 0; i < raw; i++) {
		if (pos == raw_status[i])
			return 0;
		if (pos == raw_status[i] + raw - i)
			return 0;
		if (pos == raw_status[i] - (raw - i))
			return 0;
	}
	return 1;
}

void process_raw(int raw)
{
	if (raw == N) {
		options++;
		if (options <= 100) {
			int i;
			printf("answer %2d is: ", options);
			for (i = 0; i < N; i++)
				printf("%5d", raw_status[i]);
			printf("\n");
		}
	} else {
		int pos;
		for (pos = 0; pos < N; pos++) {
			if (is_ok(raw, pos)) {
				raw_status[raw] = pos;
				process_raw(raw+1);
			}
		}
	}
}

int main()
{
	process_raw(0);

	printf("answer of %d queen is: %d\n", N, options);

	return 0;
}
