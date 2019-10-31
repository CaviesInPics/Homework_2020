#include <bits/stdc++.h>
#define rua system("pause")
using namespace std;
typedef long long ll;
typedef long double db;
inline int read()
{
	int x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
	while (isdigit(c)) {x = x * 10 + c - '0', c = getchar();}
	return x * f;
}

int n, c, l[10], p[10];
db f[2][35][305], ans;

int main()
{
	n = read(), c = read();
	for (int i = 1; i <= n; i ++) l[i] = read();
	sort(l + 1, l + 1 + n);
	for (int i = 1; i < n; i ++) p[i] = i;
	do
	{
		memset(f, 0, sizeof f);
		int mx = (1 << (n - 1)), len = c * n;
		f[0][0][min(l[n] * n, len)] = 1;
		for (int i = 1; i < len; i ++)
		{
			int np = i & 1, p = np ^ 1;
			if (i % n == 0)
			{
				swap(f[np], f[p]);
				continue;
			}
			memset(f[np], 0, sizeof f[np]);
			for (int s = 0; s < mx; s ++)
				for (int j = i; j <= len; j ++)
					if (f[p][s][j])
					{
						db now = f[p][s][j];
						int cur = i % n;
						f[np][s][j] += now;
						if (s & (1 << (cur - 1))) continue;
						f[np][s | (1 << (cur - 1))][min(len, max(j, i + l[::p[cur]] * n))] += now;
					}
		}
		ans += f[(len - 1) & 1][mx - 1][len];
	} while (next_permutation(p + 1, p + n));
	db down = 1;
	for (int i = 1; i < n; i ++) down = down * i * c;
	ans /= down;
	printf("%.11lf\n", (double)ans);
	return 0;
}
