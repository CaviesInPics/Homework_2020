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

const int MOD = 1e9 + 7;
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

const int MAXN = 5e5 + 10;
const int MAXM = 1e7 + 10;

int n, prime[MAXM >> 2], pcnt, mn[MAXM], mu[MAXM];
bool mark[MAXM];
vector<int> fact[MAXN];

void init(int n)
{
	mu[1] = 1, mn[1] = 1;
	for (int i = 2; i <= n; i ++)
	{
		if (!mark[i]) prime[++ pcnt] = i, mn[i] = i, mu[i] = MOD - 1;
		for (int j = 1; j <= pcnt; j ++)
		{
			int np = prime[j], now = np * i;
			if (now > n) break;
			mark[now] = 1;
			if (mn[i] == np) {mn[now] = np; break;}
			mn[now] = np, mu[now] = mu[i] ? MOD - mu[i] : 0;
		}
	}
}

void divide(int x, int _x)
{
	while (x > 1)
	{
		int y = mn[x];
		fact[_x].push_back(y), x /= y;
		while ((x % y) == 0) x /= y;
	}
}

int cnt[MAXM], pw[MAXN], a[MAXN];

void dfs(int id, int x, int now)
{
	if (x == fact[id].size()) return (void)cnt[now] ++;
	dfs(id, x + 1, now), dfs(id, x + 1, now * fact[id][x]);
}

int dfs2(int id, int x, int now)
{
	if (!cnt[now]) return 0;
	if (x == fact[id].size())
		return now == 1 ? 0 : mul(mu[now], inc(pw[cnt[now]], MOD - 1));
	return inc(dfs2(id, x + 1, now), dfs2(id, x + 1, now * fact[id][x]));
}

int main()
{
	init(1e7), n = read(), pw[0] = 1;
	for (int i = 1; i <= n; i ++) a[i] = read(), divide(a[i], i), pw[i] = inc(pw[i - 1], pw[i - 1]);
	for (int i = 1; i <= n; i ++) dfs(i, 0, 1);
	int all = pw[n], ans = 0;
	for (int i = 2; i <= 1e7; i ++)
		if (cnt[i] && mu[i]) add(all, mul(mu[i], inc(pw[cnt[i]], MOD - 1))); // cerr << i << " " << cnt[i] << " " << mu[i] << " " << all << endl;
	all = inc(pw[n], MOD - all);
	for (int i = 1; i <= n; i ++)
		add(ans, inc(all, dfs2(i, 0, 1)));
	cout << ans << endl;
	return 0;
}
