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
 *             ()A[n], (A[n]), A[n]()
 *   ()A[n], A[n]()表示同一个序列，当且仅当A[n]没有括号嵌套，即()...()()
 *   对于任意n>0，这样的序列只有1个，用B[n]表示n对括号的所以合法组合数目，有
 *             B[1] = 1;
 *             B[2] = 2;
 *             B[3] = 5;
 *             B[n] = 3 * B[n-1] - 1;
 *             B[n] = (3^(n-1) + 1) / 2;
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//返回B[n], n >= 1
int fun(int n)
{
	int i;
	int ans = 1;
	for (i = 0; i < n - 1; i++)
		ans *= 3;
	ans = (ans + 1) / 2;
	return ans;
}

/*
 *   Note: The returned array must be malloced, assume caller calls free().
 */
char *generateParenthesis(int n, int* returnSize)
{
	*returnSize = fun(n);
	char *strs = malloc(*returnSize * (2 * n + 1));
	if (strs == NULL) {
		printf("alloc memory failed\n");
		return NULL;
	}

	int i, j, bn;
	int str_size = 2 * n + 1;

	strcpy(strs, "()");
	//按照括号对数循环，从1对括号逐步生成n对括号
	for (i = 1, bn = 1; i < n; i++) {
		//(A[n])模式生成
		for (j = 0; j < bn; j++) {
			strs[(bn + j) * str_size] = '(';
			strcpy(strs + (bn + j) * str_size + 1, strs + j * str_size);
			strs[(bn + j) * str_size + i * 2 + 1] = ')';
			strs[(bn + j) * str_size + i * 2 + 2] = '\0';
		}
		//()A[n]模式生成
		for (j = 0; j < bn - 1; j++) {
			strs[(bn * 2 + j) * str_size] = '(';
			strs[(bn * 2 + j) * str_size + 1] = ')';
			strcpy(strs + (bn * 2 + j) * str_size + 2, strs + (j + 1) * str_size);
		}
		//A[n]()模式生成
		for (j = 0; j < bn; j++)
			strcpy(strs + j * str_size + i * 2, "()");
		bn = bn * 3 - 1;
	}

	return strs;
}

/*
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
	*returnSize = fun(n) + 200;
	int str_num = 0;
	char *strs = malloc((*returnSize + 1) * (2 * n + 1));
	if (strs == NULL) {
		printf("malloc memory failed\n");
		return NULL;
	}
	strs[(*returnSize + 1) * (2 * n + 1) - 1] = '\0';

	dfs(strs, &str_num, strs + *returnSize * (2 * n + 1), 0, 0, n);

	*returnSize = str_num;
	return strs;
}

int main()
{
	int i, j;
	int returnSize = 0;
	char *strs = NULL;

	for (i = 1; i < 9; i++) {
		strs = generateParenthesis(i, &returnSize);
		if (strs != NULL) {
			printf("strings of %d pairs of braces\n", i);
			if ( i < 7) {
				for (j = 0; j < returnSize; j++)
					printf("%s\n", strs + j * (2 * i + 1));
			}
			printf("total: %d\n", returnSize);
			free(strs);
		} else {
			printf("error while n=%d\n", i);
			break;
		}
		strs = generateParenthesis2(i, &returnSize);
		if (strs != NULL) {
			printf("strings of %d pairs of braces, use dfs\n", i);
			if ( i < 7) {
				for (j = 0; j < returnSize; j++)
					printf("%s\n", strs + j * (2 * i + 1));
			}
			printf("total: %d\n", returnSize);
			free(strs);
		} else {
			printf("error while n=%d\n", i);
			break;
		}
	}

	return 0;
}

