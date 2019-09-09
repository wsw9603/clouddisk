/*
 * 题目描述
 *   编写一个飞行路径规划程序，给定起始机场、必经机场以及终止机场，输出最短飞行
 *   路径。路径中每个机场最多只能出现一次；如果起始机场和终止机场相同，该机场可
 *   以且只能出现2次。
 * 几个名词解释
 *   ##直达航线
 *     直达航线是飞机在两个机场之间的飞行路线，是双向的。
 *     任意两个机场之间最多存在一条直达航线。
 *   ##必经机场
 *     要求飞机途中必须要经过的机场。存在多个必经机场时，不限制经过顺序。
 *   ##普通机场
 *     除了起始机场、终止机场和必经机场之外的所有机场，不限制飞机是否经过。
 *
 * 解答要求
 *   时间限制：1000ms，内存限制：256MB
 *   输入
 *     1.第一行为带设置的直达航线机场组数N，N>0
 *     2.接着N行为直达航线机场标志及距离，其中第一个数字为机场标识ID1，第二个数
 *       字为机场标识ID2，第三个数字为机场ID1和机场ID2之间的直线距离，数字之间
 *       使用空格隔开。
 *     3.接着一行是设置起始机场标识ID
 *     4.接着一行是设置终止机场标识ID
 *     5.接着一行是输入必经机场个数M，M>=0
 *     6.接着M行为必经机场标识ID
 *   输入规格
 *     ##每个机场用唯一ID标识。
 *     ##用例输入设置机场ID1和机场ID2之间的直达航线距离Km，用例保证不重复设置同
 *       一条直达航线，且直达航线的距离大于0。
 *     ##必经机场数目>=0，且必经机场不包含起始和终止机场，用例保证必经机场ID之
 *       间不重复。
 *  样例
 *    输入
 *      6
 *      1 2 2000
 *      1 3 2000
 *      1 4 4000
 *      2 5 1000
 *      3 4 1000
 *      4 5 500
 *      1
 *      1
 *      2
 *      4
 *      5
 *    输出
 *      6500
 *
 * 设计
 *   深度优先搜索dfs
 *   https://www.cnblogs.com/thousfeet/p/9229395.html
 */

#include <stdio.h>

//最大节点数目
#define MAX_SIZE 100
#define MAX_INT 1000000

static int map[MAX_SIZE][MAX_SIZE];
static int books[MAX_SIZE];	//记录已经走过的路径
static int must[MAX_SIZE];	//记录必经之路
static int min_dit;	//起点到终点满足条件的最短距离
static int dest;	//终点
static int start;	//起点
static int point_num;	//机场数目
static int must_num;	//必经机场数目

int is_include_all_must()
{
	int i;
	for (i = 0; i < must_num; i++)
		if (books[must[i]] == 0)
			return 0;
	return 1;
}
/*
 * cur记录当前遍历到的节点，dst表示从起点到当前节点的距离
 */
void dfs(int cur, int dit)
{
	//已经超过最短路线，继续走下去也没有意义
	if (dit >= min_dit)
		return;
	//到达目的地
	if (books[dest] == 1) {
		if (dit < min_dit && is_include_all_must())
			min_dit = dit;
		return;
	}

	int i;
	for (i = 0; i < point_num; i++) {
		if (books[i] == 0 && map[cur][i] != MAX_INT) {
			books[i] = 1;
			dfs(i, dit + map[cur][i]);
			books[i] = 0;
		}
	}
}

int main()
{
	int i, j, edges, id1, id2, distance;

	//初始化
	min_dit = MAX_INT;
	for (i = 0; i < MAX_SIZE; i++)
		for (j = 0; j < MAX_SIZE; j++)
			map[i][j] = MAX_INT;
	for (i = 0; i < MAX_SIZE; i++)
		map[i][i] = 0;
	//边数目和边长度
	scanf("%d", &edges);
	for (i = 0; i < edges; i++) {
		scanf("%d %d %d", &id1, &id2, &distance);
		map[id1 - 1][id2 - 1] = distance;
		map[id2 - 1][id1 - 1] = distance;
	}
	//假设机场距离是按照机场编号从小到大的顺序输入的
	point_num = id2;
	//起始机场和终止机场
	scanf("%d\n%d", &start, &dest);
	start--;
	dest--;
	scanf("%d", &must_num);
	for (i = 0; i < must_num; i++) {
		scanf("%d", &must[i]);
		must[i]--;
	}

	if (start != dest)
		books[start] = 1;
	dfs(start, 0);

	printf("%d", min_dit);
}
