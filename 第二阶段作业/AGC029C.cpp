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

const int MAXN = 4e5 + 10;
int n, a[MAXN], st[MAXN], top, val[MAXN];

inline bool check(int x)
{
	st[top = 1] = 1, val[1] = 0;
	for (int i = 2; i <= n; i ++)
	{
		if (a[i] > a[i - 1])
		{
			if (val[top])
			{
				val[++ top] = 0, st[top] = a[i - 1] + 1;
			}
			continue;
		}
		if (!x) return 0;
		while (top && st[top] > a[i]) top --;
		if (!top) return 0;
		while (top > 1 && val[top] == val[top - 1]) top --;
		if (top == 1 && val[1] == x) return 0;
		if (val[top] == x)
		{
			int pre = val[top - 1];
			if (st[top - 1] < st[top] - 1)
			{
				int cur = st[top];
				st[top] --, val[top] = pre + 1;
				st[++ top] = cur, val[top] = 0;
			}
			else
			{
				if (top <= 2 || val[top - 2] != val[top - 1] + 1)
					val[top - 1] ++, val[top] = 0;
				else st[top - 1] = st[top], val[top - 1] = 0, top --;
			}
		}
		else
		{
			int pre = val[top];
			if (st[top] < a[i])
				st[++ top] = a[i];
			val[top] = pre + 1;
		}
	}
	return 1;
}

int main()
{
//	freopen("in21.txt", "r", stdin);
	n = read();
	for (int i = 1; i <= n; i ++) a[i] = read();
	int L = 1, R = n, res = n;
	while (L <= R)
	{
		int MID = (L + R) >> 1;
		if (check(MID - 1)) res = MID, R = MID - 1;
		else L = MID + 1;
	}
	cout << res << endl;
	return 0;
}
