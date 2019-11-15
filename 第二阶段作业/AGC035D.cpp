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
typedef pair<int, int> mypair;

int n, a[20];
map<mypair, ll> f[20][20];
ll dfs(int l, int r, int x, int y)
{
	if (l == r - 1) return 1LL * a[l] * x + 1LL * a[r] * y;
	mypair now(x, y);
	if (f[l][r].count(now))
		return f[l][r][now];
	ll res = 1LL << 60;
	for (int i = l + 1; i < r; i ++)
		res = min(res, dfs(l, i, x, x + y) + dfs(i, r, x + y, y) - 1LL * a[i] * (x + y));
	return f[l][r][now] = res;
}

int main()
{
	n = read();
	for (int i = 1; i <= n; i ++) a[i] = read();
	printf("%lld\n", dfs(1, n, 1, 1));
	return 0;
}
