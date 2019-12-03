#include <bits/stdc++.h>
#define rua system("pause")
using namespace std;
typedef long long ll;
inline ll read()
{
	ll x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
	while (isdigit(c)) {x = x * 10 + c - '0', c = getchar();}
	return x * f;
}

const int MAXN = 2005;
struct edge
{
	int u, v, w;
	edge() {}
	edge(int u, int v, int w): u(u), v(v), w(w) {}
	inline bool operator < (const edge &rhs) const {return w < rhs.w;}
} e[MAXN];
typedef pair<int, int> mypair;
vector<mypair> linker[MAXN];
int n, m, pnt[MAXN], ontree[MAXN], dep[MAXN], fa[MAXN][12], mx[MAXN][12]; ll W, S;
inline int find(int x) {while (x ^ pnt[x]) x = pnt[x] = pnt[pnt[x]]; return x;}

#define fi first
#define se second

void dfs(int x)
{
	dep[x] = dep[fa[x][0]] + 1;
	for (int i = 1; i <= 10; i ++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i = 1; i <= 10; i ++) mx[x][i] = max(mx[x][i - 1], mx[fa[x][i - 1]][i - 1]);
	for (auto cur : linker[x])
		if (cur.fi != fa[x][0])
			fa[cur.fi][0] = x, mx[cur.fi][0] = cur.se, dfs(cur.fi);
}

int query(int u, int v)
{
	int res = 0;
	if (dep[u] != dep[v])
	{
		if (dep[u] < dep[v]) swap(u, v);
		for (int i = 10; i >= 0; i --)
			if (dep[fa[u][i]] >= dep[v])
				res = max(res, mx[u][i]), u = fa[u][i];
	}
	if (u == v) return res;
	for (int i = 10; i >= 0; i --)
		if (fa[u][i] != fa[v][i])
			res = max(res, max(mx[u][i], mx[v][i])), u = fa[u][i], v = fa[v][i];
	return max(res, max(mx[u][0], mx[v][0]));
}

const int MOD = 1e9 + 7;
inline int inc(int x, int y) {x += y; return x >= MOD ? x - MOD : x;}
inline void add(int &x, int y) {y += x; x = y >= MOD ? y - MOD : y;}
inline int mul(int x, int y) {return 1LL * x * y % MOD;}
inline int qpow(int x, int y)
{
	if (y < 0) return 1;
	int res = 1;
	for (; y; y >>= 1, x = mul(x, x))
		if (y & 1) res = mul(res, x);
	return res;
}

int main()
{
//	freopen("01.txt", "r", stdin);
	n = read(), m = read(), W = read();
	for (int i = 1; i <= m; i ++)	
		e[i].u = read(), e[i].v = read(), e[i].w = read();
	sort(e + 1, e + 1 + m);
	for (int i = 1; i <= n; i ++) pnt[i] = i;
	for (int i = 1; i <= m; i ++)
	{
		int u = find(e[i].u), v = find(e[i].v);
		if (u == v) continue; pnt[u] = v, ontree[i] = 1;
		linker[e[i].u].emplace_back(e[i].v, e[i].w);
		linker[e[i].v].emplace_back(e[i].u, e[i].w);
		S += e[i].w;
		if (S > W) return puts("0"), 0;
	}
	dfs(1);
	if (S == W)
	{
		int cnt = n - 1;
		for (int i = 1; i <= m; i ++)
			if (!ontree[i] && query(e[i].u, e[i].v) == e[i].w) cnt ++;
		printf("%d\n", (MOD + qpow(2, m) - qpow(2, m - cnt + 1)) % MOD);
	}
	else
	{
		W -= S; int cnt = 0, mn = 0;
		for (int i = 1; i <= m; i ++)
			if (!ontree[i])
			{
				int d = e[i].w - query(e[i].u, e[i].v);
				if (d == W) cnt ++;
				else if (d < W) mn ++;
			}
		printf("%lld\n", (2LL * (qpow(2, cnt) - 1) * qpow(2, m - (n - 1 + mn + cnt))) % MOD);
	}
	return 0;
}
