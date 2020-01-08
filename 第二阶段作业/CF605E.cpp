#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read()
{
	int x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
	while (isdigit(c)) {x = x * 10 + c - '0', c = getchar();}
	return x * f;
}

typedef long double db;
const int maxn = 1005;
int n, vis[maxn]; db p[maxn][maxn], mul[maxn], f[maxn];

int main()
{
	n = read();
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
		{
			int x = read();
			p[i][j] = 1.0 * x / 100;
		}
	for (int i = 1; i < n; i ++) f[i] = 1;
	vis[n] = 1, mul[n] = 1, f[n] = 0;
	for (int i = 1; i < n; i ++) mul[i] = 1 - p[i][n];
	for (int i = 1; i < n; i ++)
	{
		db mn = 1e20; int pos = 0;
		for (int j = 1; j <= n; j ++)
			if (!vis[j] && f[j] / (1 - mul[j]) < mn)
				pos = j, mn = f[j] / (1 - mul[j]);
		vis[pos] = 1, f[pos] /= 1 - mul[pos];
		for (int j = 1; j <= n; j ++)
			if (!vis[j]) f[j] += f[pos] * p[j][pos] * mul[j], mul[j] *= 1 - p[j][pos];
	}
	printf("%.10lf\n", (double)f[1]);
	return 0;
}