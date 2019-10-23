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

const int MOD = 1e9 + 7;
const int Inv2 = (MOD + 1) / 2;
inline int inc(int x, int y) {x += y; return x >= MOD ? x - MOD : x;}
inline void add(int &x, int y) {y += x; x = y >= MOD ? y - MOD : y;}
inline int mul(int x, int y) {return (ll)x * y % MOD;}
inline int qpow(int x, int y)
{
	int res = 1;
	for (; y; y >>= 1, x = mul(x, x))
		if (y & 1) res = mul(res, x);
	return res;
}

const int MAXN = 3005;
int n, Q, f[MAXN][MAXN], A[MAXN], tmp[MAXN][MAXN];

int main()
{
	n = read(), Q = read();
	for (int i = 1; i <= n; i ++) A[i] = read();
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			if (A[i] > A[j]) f[i][j] = 1;
	for (int i = 1; i <= Q; i ++)
	{
		int x = read(), y = read();
		if (x == y) continue;
		if (x > y) swap(x, y);
		for (int j = 1; j <= n; j ++)
			tmp[x][j] = f[x][j], tmp[j][x] = f[j][x],
			tmp[y][j] = f[y][j], tmp[j][y] = f[j][y];
		for (int j = 1; j <= n; j ++) if (j != x && j != y)
			f[y][j] = f[x][j] = mul(Inv2, inc(tmp[x][j], tmp[y][j])),
			f[j][x] = f[j][y] = mul(Inv2, inc(tmp[j][x], tmp[j][y]));
		f[x][y] = f[y][x] = mul(Inv2, inc(tmp[x][y], tmp[y][x]));
	}
	int ans = 0;
	for (int i = 1; i <= n; i ++)
		for (int j = i + 1; j <= n; j ++)
			add(ans, f[i][j]);
	printf("%d\n", mul(ans, qpow(2, Q)));
	return 0;
}
