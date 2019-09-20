/*
 * 输入两个字符串s和p，输出s最少删除多少字符使得p是s的子串
 */

#include <stdio.h>
#include <string.h>

#define MAX_INT 0x7FFFFFFF

int fun(char *s, char *p)
{
	int i, skip, min_skip = MAX_INT;
	while (*s) {
		char *temp = p;
		while (*s && *s++ != *temp);
		if (!*s)
			continue;
		temp++;
		if (!*temp)
			return 0;
		skip = 0;
		for (i = 0; s[i]; i++) {
			if (s[i] == *temp) {
				temp++;
				if (!*temp) {
					min_skip = min_skip > skip ? skip : min_skip;
					break;
				}
			}
			else
				skip++;
		}
		s++;
	}
	return min_skip;
}

int main()
{
	char s[100], p[100];
	scanf("%s %s", s, p);
	printf("%d\n", fun(s, p));

	return 0;
}
