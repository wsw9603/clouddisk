/*
 * 输入
 * 第一行两个数n和m，表示对象的数量和输入的关系数量
 * 接下来的m行分别为1条关系
 * 输出
 * 分三种情况
 * 关系冲突
 * 关系不足以将所有对象排列
 * 前i条关系就可以将所有关系排列，则忽略后面的关系，输出i以及排列好的对象
 *
 * 示例
 * 4 6
 * A<B
 * A<C
 * B<C
 * C<D
 * B<D
 * A<D
 *
 * 用有向图来描述所有对象的关系，当能够从一个节点出发，遍历整张图时则可以将
 * 所有对象排列好，如果出现环，则说明条件冲突。
 */

#include <stdio.h>

#define MAX_NR_NODE 26

#define FOUND      0
#define NOFOUND   -1
#define CIRCLE    -2

#define MARKED     1
#define UNMARK     0

#define REACHABLE  1
#define UNREACHABLE 0

int map[MAX_NR_NODE][MAX_NR_NODE];
int book[MAX_NR_NODE];		//表示每个节点是否走过
char trace[MAX_NR_NODE + 1];	//记录遍历时走过的路径

/* 深度优先搜索，找到一条路径或者有环则退出，或者最后找不到路径退出 */
int dfs(int cur, int deepth, int n)
{
	trace[deepth-1] = 'A' + cur;
	if (deepth == n)
		return FOUND;

	int i;
	for (i = 0; i < n; i++) {
		if (map[cur][i] == UNREACHABLE)
			continue;
		if (book[i] == MARKED)
			return CIRCLE;	//可以从i到达，而且已经走过，说明有环
		book[i] = MARKED;
		switch (dfs(i, deepth + 1, n)) {
			case FOUND: return FOUND;
			case CIRCLE: return CIRCLE;
			case NOFOUND: break;
		}
		book[i] = UNMARK;
	}
}

int main()
{
	int n, m, i, j;
	scanf("%d %d", &n, &m);

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			map[i][j] = UNREACHABLE;
	for (i = 0; i < n; i++)
		book[i] = UNMARK;
	trace[n] = '\0';

	char a, b;
	int flag = NOFOUND;
	for (i = 0; i < m; i++) {
		scanf("\n%c<%c", &a, &b);
		if (flag == FOUND || flag == CIRCLE)
			continue;
		map[a - 'A'][b - 'A'] = REACHABLE;
		for (j = 0; j < n; j++) {
			book[j] = MARKED;
			int status = dfs(j, 1, n);
			switch (status) {
				case FOUND:
					printf("found i = %d trace: %s\n", i, trace);
					flag = FOUND;
					break;
				case CIRCLE:
					printf("confilict\n");
					flag = CIRCLE;
					break;
				case NOFOUND:
					break;
			}
			book[j] = UNMARK;
			if (flag == FOUND || flag == CIRCLE)
				break;
		}
	}

	if (flag == NOFOUND)
		printf("nofound");

	return -1;
}
