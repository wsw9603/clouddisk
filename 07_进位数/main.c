/*
 * 输入
 * 两个数a，b (1 <=a < b <= 1000 000 000)
 * 输出
 * 从a到b的所有整数以二进制表示，并求和的过程中产生的进位次数。
 *
 * 示例输入
 * 1 3
 * 输出
 * 2
 * 分析：01 + 10 + 11 = 11 + 11 = 110，只有在后一次计算中产生了两次进位。
 *
 * 观察二进制进位的加法可以发现每次进位只是两个低位的1生成了一个高位的1，
 * 因此，只需要对比和的二进制表示中1的个数和两个加数的二进制表示中1的个数
 * 的差就能得到进位次数。
 * 进一步，所有加数和的二进制表示中1的个数与每个加数的二进制表示中1的个数
 * 和相比较就可以得到整个过程中的进位次数。
 * a到b的所有数字的和为 (a + b) * (b - a + 1) / 2
 * 用 sum & (sum - 1) 的方法求1的个数，但是求所有的加数的二进制表示中1的
 * 个数不能用这种方法，可能会超时。
 *
 * 用动态规划的方法求，a到b的所有数字的二进制表示中1的个数
 *   dp[a] 表示a的二进制表示中1的个数
 *   注意到2^n的二进制表示中只有1个1， 10000...00
 *   如果有 a = 2^n + b 且b和2^n相加时不发生二进制的进位
 *   则 dp[a] = dp[b] + 1
 *   为了保证不发生二进制进位，我们直接假设2^n > b
 *
 * 000
 * 001
 * 010
 * 011
 * 100
 * 101
 * 110
 * 111
 * 可以观察到：第一位上每两个数出现一次1，第二位上每4个数出现两个1，以此类推，
 * 可以得到从0到a的所有数的二进制表示中1的个数总和。
 */

#include <stdio.h>
#include <sys/time.h>

#define MAX_NUM 1000000000
int dp[MAX_NUM] = {0};

/*
 * 求0到b之间的每个数字的二进制表示中1的个数
 */
void fun(unsigned long b)
{
	int n;
	unsigned long i;

	dp[0] = 0;
	dp[1] = 1;

	for (n = 1; 1UL << (n + 1) <= b; n++)
		for (i = 0; i < 1UL << n; i++)
			dp[i + (1UL << n)] = 1 + dp[i];

	for (i = 0; i + (1UL << n) <= b; i++)
		dp[i + (1UL << n)] = 1 + dp[i];
}

/*
 * 输出0到a的所有数的二进制表示中1的个数
 */
int ones_below_a(unsigned long a)
{
	int k, sum = 0;
	a++;
	for (k = 0; a > 1 << k; k++) {
		sum += a / (1 << (k + 1)) * (1 << k);
		int temp = a % (1 << (k + 1));
		sum += temp > (1 << k) ? temp - (1 << k) : 0;
	}
	printf("a: %lu, sum: %d\n", --a, sum);
	return sum;
}

int main()
{
	unsigned long a, b, sum, temp, clonea;
	int ones_in_sum, ones_per_ele, ones_total_ele;
struct timeval start_time, end_time;

	scanf("%lu %lu", &a, &b);
	sum = (a + b) * (b - a + 1UL) / 2UL;
	for (ones_in_sum = 0; sum != 0; sum &= sum - 1UL, ones_in_sum++);

	printf("answer is %d\n", ones_below_a(b) - ones_below_a(a-1) - ones_in_sum);

gettimeofday(&start_time, NULL);
clonea = a;
	for (ones_total_ele = 0; a <= b; a++) {
		for (ones_per_ele = 0, temp = a; temp != 0; temp &= temp - 1UL, ones_per_ele++);
		ones_total_ele += ones_per_ele;
	}
	printf("%d", ones_total_ele - ones_in_sum);
gettimeofday(&end_time, NULL);
printf("\nfirst function start at %ld sec, %ld usec\n"
	"end at %ld sec, %ld usec\n"
	"duriance %ld sec, %ld usec\n", start_time.tv_sec, start_time.tv_usec,
	end_time.tv_sec, end_time.tv_usec, end_time.tv_sec - start_time.tv_sec, end_time.tv_usec - start_time.tv_usec);

gettimeofday(&start_time, NULL);
a = clonea;
	fun(b);
	for (ones_total_ele = 0; a <= b; a++)
		ones_total_ele += dp[a];

	printf("%d", ones_total_ele - ones_in_sum);
gettimeofday(&end_time, NULL);
printf("\nsecond function start at %ld sec, %ld usec\n"
	"end at %ld sec, %ld usec\n"
	"duriance %ld sec, %ld usec\n", start_time.tv_sec, start_time.tv_usec,
	end_time.tv_sec, end_time.tv_usec, end_time.tv_sec - start_time.tv_sec, end_time.tv_usec - start_time.tv_usec);

	return 0;
}
