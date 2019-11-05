#include <bits/stdc++.h>
#define rua system("pause")
using namespace std;
typedef long long ll;
inline int read()
{
	int x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
	while (isdigit(c)) {x = x * 10 + c - '0', c = getchar();}
	return x * f;
}

const int MAXN = 1005;
int n, x[MAXN], y[MAXN], m = 31;

string Solve(int x, int y, int st)
{
	if (st == -1) {return "";}
	if (abs(y) < abs(x))
	{
		if (x > 0) return Solve(x - (1 << st), y, st - 1) + "R";
		else return Solve(x + (1 << st), y, st - 1) + 'L';
	}
	else
	{
		if (y > 0) return Solve(x, y - (1 << st), st - 1) + "U";
		else return Solve(x, y + (1 << st), st - 1) + "D";
	}
}

int main()
{
//	freopen("input.txt", "r", stdin);
	n = read();
	for (int i = 1; i <= n; i ++) x[i] = read(), y[i] = read();
	int foo = (abs(x[1]) + abs(y[1])) % 2;
	for (int i = 2; i <= n; i ++)
		if ((abs(x[i]) + abs(y[i])) % 2 != foo)
			return puts("-1"), 0;
	if (!foo)
	{
		printf("%d\n", m + 1);
		for (int i = 0; i < m; i ++)
			printf("%d ", 1 << i);
		puts("1");
		for (int i = 1; i <= n; i ++)
			cout << Solve(x[i] - 1, y[i], 30) + "R" << endl;
	}
	else
	{
		printf("%d\n", m);
		for (int i = 0; i < m; i ++)
			printf("%d ", 1 << i);
		puts("");
		for (int i = 1; i <= n; i ++)
			cout << Solve(x[i], y[i], 30) << endl;
	}
	return 0;
} 
