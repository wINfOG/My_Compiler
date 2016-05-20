#include <stdio.h>
#include <stdlib.h>
char t;
void expr(int k);
void expr2(int k);
void factor(void);
int prec(char t);
char gettok(void);

int calstack[256] = { 0 };
int i = 0;
int result = 0;
void push(char t);


int main(void)
{
	t = gettok();
	expr2(0);
	printf("\nresult = %d  ", calstack[0]);
	return 0;
}
//表达式分析部分1,未优化的
void expr(int k)
{
	if (k > 2) factor();
	else
	{
		expr(k + 1);
		while (prec(t) == k)
		{
			//保存t状态
			char op = t;
			t = gettok();
			expr(k + 1);
			printf("use op %c\n", op);
			push(op);
		}
	}
}
//部分2进行优化的
void expr2(int k)
{
	int k1;
	factor();
	for (k1 = prec(t); k1 >= k; k1--)
	{
		while (prec(t) == k1)
		{
			//保存t状态
			char op = t;
			t = gettok();
			expr2(k1 + 1);
			printf("use op %c\n", op);
			push(op);
		}
	}
}
char gettok(void)
{
	return getchar();
}
int prec(char t)
{
	if (t == '+' || t == '-')
		return 1;
	else if (t == '*' || t == '/')
		return 2;
	else if (t == '\n')
		return -1;
	else
		printf("Error unknow charactor t = %c  %x\n", t, t);

	return 3;
}
void factor()
{
	printf("num:%c\n", t);
	push(t);
	t = gettok();
}
//输出计算部分
void push(char t)
{
	switch (t)
	{
	case '+':
		i--; calstack[i - 1] = calstack[i - 1] + calstack[i];
		break;
	case '-':
		i--; calstack[i - 1] = calstack[i - 1] - calstack[i];
		break;
	case '*':
		i--; calstack[i - 1] = calstack[i - 1] * calstack[i];
		break;
	case '/':
		i--; calstack[i - 1] = calstack[i - 1] / calstack[i];
		break;
	default:
		calstack[i] = atoi(&t); i++;
		break;
	}
	calstack[i] = 0;
}
