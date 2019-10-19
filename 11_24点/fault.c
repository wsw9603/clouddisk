/*
 * 24点游戏
 * 给出4个数，判断能否通过加减乘除四则运算得到24
 * 给出的4个数字为A,2,3,...,10,J,Q,K,即为1~13
 *
 * 思路
 * 穷举4个数的所有可能的运算，判断计算结果是否是24
 * 每次取任意两个数计算，得到的结果取代这两个数，直到数字只剩下一个
 *
 * 1. 每次从所有数中任意选择两个进行计算，得到一个值，跟剩余的数放一起进行下次迭代计算，直到只剩一个数，判断是否是24；
 * 2. 任意两个数的计算最多有6个结果，因为除法和减法都有两种情况；
 * 3. 中间进行合理剪枝；
 * 4. 4个数的所有运算结果最多为C(4,2) * 6 * C(3,2) * 6 * C(2,2) * 6 = 3888；
 */

#include <stdio.h>
#include <string.h>

/*************************start expression_t*************************/
#define MAX_EXP_LEN 100

/* 表达式类型，记录两个操作数和一个操作符
 * 为了方便处理，新增定义两种运算符
 * a: n1 a n2 = n2 - n1
 * b: n1 b n2 = n2 / n1
 */

typedef struct {
	double num1;
	double num2;
	char operator;	//支持加减乘除4种操作符
} expression_t;

/* 获取表达式的计算结果，表达式错误的情况暂未处理 */
double get_exp_val(expression_t *exp)
{
	switch (exp->operator) {
		case '+': return exp->num1 + exp->num2;
		case '-': return exp->num1 - exp->num2;
		case '*': return exp->num1 * exp->num2;
		case '/': return exp->num1 / exp->num2;
		case 'a': return exp->num2 - exp->num1;
		case 'b': return exp->num2 / exp->num1;
		default:
		printf("unsupported operator\n");
		return -1;
	}
}

/* 表达式的字符串形式 */
void print_expression(expression_t *exp)
{
	printf("%lf %c %lf = %lf\n", exp->num1, exp->num2,
		 exp->operator, get_exp_val(exp));
}
/************************end expression_t****************************/
/*******************一次计算过程*************************/

#define STEPS_PER_PROCESS 3

typedef struct {
	int nr_num;
	double operands[STEPS_PER_PROCESS + 1];
	expression_t exps[STEPS_PER_PROCESS];
} process_t;

/******************************end process_t*************************/

double dfs(process_t *pro)
{
	if (pro->nr_num == 1)
		return pro->operands[0];

	pro->nr_num--;
	int op1, op2, i;
	expression_t *exp = &pro->exps[STEPS_PER_PROCESS + 1 - pro->nr_num];
	for (op1 = 0; op1 < pro->nr_num; op1++) {
		exp->num1 = pro->operands[op1];
		for (op2 = op1 + 1; op2 <= pro->nr_num; op2++) {
			exp->num2 = pro->operands[op2];
			//后面的数字向前移动一步
			for (i = op2; i < pro->nr_num; i++)
				pro->operands[i] = pro->operands[i + 1];
			char ops[] = {'+', '-', '*', '/', 'a', 'b'};
			for (i = 0; i < sizeof(ops); i++) {
				if (ops[i] == '/' && exp->num2 == 0.0 ||
				    ops[i] == 'b' && exp->num1 == 0.0)
					continue;
				exp->operator = ops[i];
print_expression(exp);
				pro->operands[op1] = get_exp_val(exp);
				double result = dfs(pro);
				if (result == 24.0)
					return result;
			}
			//恢复之前的数字
			for (i = pro->nr_num; i > op2; i--)
				pro->operands[i] = pro->operands[i - 1];
			pro->operands[op2] = exp->num2;
		}
		pro->operands[op1] = exp->num1 ;
	}

	pro->nr_num++;
	return -1;
}

int main()
{
	process_t pro = { .nr_num = 4, .operands = {1, 2, 3, 4}, };
	dfs(&pro);
int i;
	scanf("%d", &i);
	return 0;
}
