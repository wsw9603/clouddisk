/*
 * 给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。
 *
 * 例如，给出 n = 3，生成结果为：
 *
 * [
 *   "((()))",
 *   "(()())",
 *   "(())()",
 *   "()(())",
 *   "()()()"
 * ]
 *
 *           来源：力扣（LeetCode）
 *           链接：https://leetcode-cn.com/problems/generate-parentheses
 *           著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 *
 * 分析
 *   A[n]表示n对括号的序列，则n+1对括号的序列
 *   A[n+1]可以为
 *             (A[i])A[j]   其中i+j = n, i, j是非负数
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BRACKETS_NUM 99

/*
 * num[i]表示i对括号能够组成的和法序列数目；
 * sum[i]表示前i对括号能够组成的合法序列数目的和；
 * n >= 1
 * 动态规划思想
 * dp[n] = sum{dp[i] * dp[j]}, i,j >= 0, i+j = n-1;
 * dp[0] = dp[1] = 1;
 */
void get_series_num(int n, int num[], int sum[])
{
	int i, j;
	num[0] = num[1] = 1;
	sum[0] = 1;
	sum[1] = 2;
	for (i = 2; i <= n; i++) {
		num[i] = 0;
		for (j = 0; j < i; j++)
			num[i] += num[j] * num[i-1-j];
		sum[i] = sum[i-1] + num[i];
	}
}

char *generateParenthesis1(int n, int *returnSize)
{
	int num[MAX_BRACKETS_NUM + 1];
	int start[MAX_BRACKETS_NUM + 2];	//start[i]表示i对括号组成的序列在字符串数组中的起始位置，有start[0] = 0;
	start[0] = 0;
	const int len_per_str = 2 * n + 1;

	get_series_num(n, num, start + 1);

	char *buf = malloc(start[n+1] * len_per_str);
	if (buf == NULL) {
		printf("alloc memory failed\n");
		return NULL;
	}

	buf[0] = '\0';
	strcpy(buf + start[1] * len_per_str, "()");

	int i;
	//i表示括号的对数
	for (i = 2; i <= n; i++) {
		int j, str_num = 0;
		for (j = 0; j < i; j++) {
			/*
			 * k和p分别表示对j对括号组成的序列和i-1-j对括号组成的
			 * 序列的循环的循环次数计数
			 */
			int k;
			for (k = 0; k < num[j]; k++) {
				int p;
				for (p = 0; p < num[i-1-j]; p++) {
					char *base = buf + (start[i] + str_num) * len_per_str;
					base[0] = '(';
					strcpy(&base[1], buf + (start[j] + k) * len_per_str);
					base[1+j*2] = ')';
					strcpy(&base[2+j*2], buf + (start[i-1-j] + p) * len_per_str);
					str_num++;
				}
			}
		}
	}

	*returnSize = start[n+1];
	return buf;
}

/*
 * 深度优先搜索法
 * 先加左括号，然后增加右括号，右括号等于n则结束
 */
void dfs(char *strs, int *str_num, char *temp, int left_num, int right_num, int n)
{
	if (right_num == n) {
		strcpy(strs + *str_num * (2 * n + 1), temp);
		(*str_num)++;
		return;
	}

	if (left_num < n) {
		temp[left_num + right_num] = '(';
		dfs(strs, str_num, temp, left_num + 1, right_num, n);
	}
	if (right_num < left_num) {
		temp[left_num + right_num] = ')';
		dfs(strs, str_num, temp, left_num, right_num + 1, n);
	}
}

/*
 * 深度优先遍历求解
 */
char *generateParenthesis2(int n, int *returnSize)
{
	int str_num = 0;
	char *strs = malloc(1000 * (2 * n + 1));
	char temp[MAX_BRACKETS_NUM * 2 + 1] = {0};
	if (strs == NULL) {
		printf("malloc memory failed\n");
		return NULL;
	}

	dfs(strs, &str_num, temp, 0, 0, n);

	*returnSize = str_num;
	return strs;
}

int main()
{
	int i, j, k;
	int returnSize1 = 0;
	int returnSize2 = 0;
	char *str1 = NULL, *str2 = NULL;

	for (i = 1; i < 8; i++) {
		str1 = generateParenthesis1(i, &returnSize1);
		if (str1 != NULL) {
			printf("strings of %d pairs of braces\n", i);
			if ( i < 7) {
				for (j = 0; j < returnSize1; j++)
					printf("%s\n", str1 + j * (2 * i + 1));
			}
			printf("total: %d\n", returnSize1);
		} else {
			printf("error while n=%d\n", i);
			break;
		}
		str2 = generateParenthesis2(i, &returnSize2);
		if (str2 != NULL) {
			printf("strings of %d pairs of braces, use dfs\n", i);
			if ( i < 7) {
				for (j = 0; j < returnSize2; j++)
					printf("%s\n", str2 + j * (2 * i + 1));
			}
			printf("total: %d\n", returnSize2);
		} else {
			printf("error while n=%d\n", i);
			break;
		}

		printf("strings that is not in strs1 is\n");
		for (k = 0; k < returnSize2; k++) {
			for (j = 0; j < returnSize1; j++)
				if (strcmp(str2 + k * (2 * i + 1), str1 + j * (2 * i + 1)) == 0)
					break;
			if (j == returnSize1)
				printf("******%s\n", str2 + k * (2 * i + 1));
		}

		free(str1);
		free(str2);
	}

	return 0;
}

