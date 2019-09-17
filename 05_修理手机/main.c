/*
 * 修理手机
 * 一个城市可以近似看成n*m的网络图，有k个维修点，h个客户，还有z个地方道路损坏
 * 不能通行，可能会导致某些客户无法到达。每个修理点有无数个员工，每个客户都需
 * 要一个员工来服务，员工去客户的位置进行服务时每走一格的距离需要花费2的代价，
 * 求服务所有的客户需要的最小代价。
 *
 * 输入
 * 第一行给出两个正数n和m, 0 < n,m < 1000
 * 第二行给出k (0<k<20)以及k个维修点的坐标
 * 第三行给出z (0<z<100)以及z个道路损坏点的坐标
 * 第四行给出h (0<h<100)已经h个客户的坐标
 * 保证客户、维修点、以及故障点都在n*m的地图里面
 * 输出
 * 输出最小的花费
 *
 * 示例
 * 输入
 * 100 100
 * 4 1 1 2 2 3 3 4 4
 * 1 1 1
 * 3 99 99 88 88 77 77
 * 输出
 * 1008
 *
 * 50 50
 * 4 1 2 3 4 5 6 7 8
 * 3 4 6 7 13 30 48
 * 3 12 13 35 19 2 48
 *
 * 50 50
 * 4 1 12 40 5 40 34 38 18
 * 10 30 15 30 16 30 17 30 18 30 19 30 20 30 21 30 22 30 23 30 30
 * 3 4 6 7 13 30 48
 *
 * 思路
 *   map二维数组上的每个点记录服务点到该点的距离，初始化为最大值；
 *   从每个维修点开始广度优先搜索，如果到达某个点的路径长度小于当前值，则更新
 *   路径长度。
 */

#include <stdio.h>

#define MAX_INT     0x7fffffff

#define MAX_SIZE    1001
#define COMMON      MAX_INT
#define SERVER      0
#define CLIENT      -1
#define BARRIER     -2

#define COMMON_BLOCK  "\e[42m  \e[0m"
#define CLIENT_BLOCK  "\e[43m  \e[0m"
#define SERVER_BLOCK "\e[44m  \e[0m"
#define BARRIER_BLOCK "\e[40m  \e[0m"

typedef struct {
	int x, y;
} point_t;

/* 约定：坐标是从1开始的，超过部分为障碍，表示不可通行 */
int map[MAX_SIZE][MAX_SIZE] = {0};
int n, m, server, client, barrier;
point_t client_points[100];
point_t server_points[100];

/*
 * 定义队列及队列操作
 */

#define MAX_ELEMENTS   10000
typedef struct {
	int head;
	int tail;			//tail指向下一个元素的位置
	point_t points[MAX_ELEMENTS];	//实际只能存放MAX_ELEMEMTS-1个元素
} queue_t;

#define init_queue(name)	queue_t name = { .head = 0, .tail = 0, }
#define is_queue_empty(q)	((q).head == (q).tail)
#define get_pos_value(pos)	map[pos.x][pos.y]
#define set_pos_value(pos, val)	map[pos.x][pos.y] = val;

point_t pop_queue(queue_t *q)
{
	int temp = q->head;
	q->head = (q->head + 1) % MAX_ELEMENTS;
	return q->points[temp];
}

void push_queue(queue_t *q, point_t pos)
{
	q->points[q->tail] = pos;
	q->tail = (q->tail + 1) % MAX_ELEMENTS;
}

void bfs(point_t pos)
{
	int called_num = 0;
	init_queue(queue);
	push_queue(&queue, pos);
	set_pos_value(pos, 0);
	while (!is_queue_empty(queue)) {
		point_t cur_pos = pop_queue(&queue);
		point_t next_pos[4]  = {{.x = cur_pos.x, .y = cur_pos.y + 1,},
					{.x = cur_pos.x, .y = cur_pos.y - 1,},
					{.x = cur_pos.x + 1, .y = cur_pos.y,},
					{.x = cur_pos.x - 1, .y = cur_pos.y,},
					};
		int i;
		int val = get_pos_value(cur_pos);
		for (i = 0; i < 4; i++) {
			if (get_pos_value(next_pos[i]) > val + 1) {
				set_pos_value(next_pos[i], val + 1);
				push_queue(&queue, next_pos[i]);
			}
		}
	}
}

void init_map()
{
	int i, j;

	scanf("%d %d", &n, &m);
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			map[i][j] = COMMON;
	for (i = 0; i <= n+1; i++) {
		map[i][0] = BARRIER;
		map[i][m+1] = BARRIER;
	}
	for (j = 1; j <= m; j++) {
		map[0][j] = BARRIER;
		map[n+1][j] = BARRIER;
	}

	scanf("%d", &server);
	for (i = 0; i < server; i++) {
		scanf("%d %d", &(server_points[i].x), &(server_points[i].y));
	}

	scanf("%d", &barrier);
	for (i = 0; i < barrier; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		map[x][y] = BARRIER;
	}

	scanf("%d", &client);
	for (i = 0; i < client; i++) {
		scanf("%d %d", &client_points[i].x, &client_points[i].y);
	}
}

void print_map()
{
	int i, j;
	for (i = 0; i <= n+1; i++) {
		for (j = 0; j <= m+1; j++) {
			switch(map[i][j]) {
				case BARRIER:printf(BARRIER_BLOCK);
					     break;
				default:
					     printf("\e[%dm%2d\e[0m",
						 41 + map[i][j] % 6,
						 map[i][j] % 100);

			}
		}
		printf("\n");
	}
}

int main()
{
	int i;
	init_map();
	print_map();

	for (i = 0; i < server; i++)
		bfs(server_points[i]);
	int sum = 0;
	for (i = 0; i < client; i++)
		sum += get_pos_value(client_points[i]);

	print_map();
	printf("%d", sum * 2);

	return 0;
}
