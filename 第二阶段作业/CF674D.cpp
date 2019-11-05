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

typedef pair<ll, int> mypair;
#define fi first
#define se second

const int MAXN = 1e5 + 10;
int n, q, deg[MAXN], fa[MAXN]; ll t[MAXN], sum[MAXN];
set<int> g[MAXN];
set<mypair> s[MAXN], big, small;
mypair get_big(int x)
{
	ll d = t[x] / deg[x];
	auto iter = s[x].end();
	auto cur = *(-- iter);
	return mypair(cur.fi + d, cur.se);
}
mypair get_small(int x)
{
	ll d = t[x] / deg[x];
	auto cur = *s[x].begin();
	return mypair(cur.fi + d, cur.se);
}
bool vis[MAXN];
inline void erase(int x)
{
	if (vis[x]) return;
	vis[x] = 1;
	s[fa[x]].erase(mypair(sum[x], x));
}
inline void clear(int x)
{
	if (vis[x]) return;
	vis[x] = 1;
	if (s[x].size())
	{
		big.erase(get_big(x));
		small.erase(get_small(x));
	}
}
inline void insert(int x)
{
	if (vis[x]) return;
	vis[x] = 1;
	if (s[x].size())
	{
		big.insert(get_big(x));
		small.insert(get_small(x));
	}
}
inline void add(int x)
{
	if (vis[x]) return;
	vis[x] = 1;
	s[fa[x]].insert(mypair(sum[x], x));
}
int main()
{
//	freopen("input.txt", "r", stdin);
	n = read(), q = read();
	for (int i = 1; i <= n; i ++) t[i] = read();
	for (int i = 1; i <= n; i ++) fa[i] = read(), deg[fa[i]] ++, deg[i] += 2, g[fa[i]].insert(i);
	for (int i = 1; i <= n; i ++)
	{
		ll now = t[i] / deg[i];
		sum[fa[i]] += now;
		sum[i] += t[i] - now * (deg[i] - 1);
	}
	for (int i = 1; i <= n; i ++)
		s[fa[i]].insert(mypair(sum[i], i));
	for (int x = 1; x <= n; x ++) if (s[x].size())
	{
		ll d = t[x] / deg[x];
		auto iter = s[x].end(); iter --;
		auto cur1 = *s[x].begin(), cur2 = *iter;
		small.insert(mypair(cur1.first + d, cur1.second));
		big.insert(mypair(cur2.first + d, cur2.second));
	}
	while (q --)
	{
		int op = read();
		if (op == 2)
		{
			int x = read();
			printf("%lld\n", t[fa[x]] / deg[fa[x]] + sum[x]);
		}
		else if (op == 3)
		{
//			assert(big.size() > 0);
			auto iter = big.end(); -- iter;
			auto cur1 = small.begin() -> fi, cur2 = iter -> fi;
			printf("%lld %lld\n", cur1, cur2);
		}
		else
		{
			int u = read(), v = read(), f = fa[u];
			vis[u] = vis[v] = vis[f] = vis[fa[f]] = vis[fa[v]] = vis[fa[fa[f]]] = vis[fa[fa[v]]] = 0;
			clear(u), clear(v), clear(f), clear(fa[f]), clear(fa[v]), clear(fa[fa[f]]), clear(fa[fa[v]]);
			vis[u] = vis[v] = vis[f] = vis[fa[f]] = vis[fa[v]] = vis[fa[fa[f]]] = vis[fa[fa[v]]] = 0;
			erase(u), erase(v), erase(f), erase(fa[f]), erase(fa[v]), erase(fa[fa[f]]), erase(fa[fa[v]]);
			sum[fa[v]] -= t[v] / deg[v], sum[fa[v]] += t[v] / (deg[v] + 1);
			sum[fa[f]] -= t[f] / deg[f], sum[fa[f]] += t[f] / (deg[f] - 1);
			sum[v] -= t[v] - t[v] / deg[v] * (deg[v] - 1), sum[v] += t[v] - t[v] / (deg[v] + 1) * deg[v];
			ll now = t[u] / deg[u]; sum[v] += now, sum[f] -= now;
			sum[f] -= t[f] - t[f] / deg[f] * (deg[f] - 1), sum[f] += t[f] - t[f] / (deg[f] - 1) * (deg[f] - 2);
			deg[v] ++, deg[f] --, fa[u] = v;
			vis[u] = vis[v] = vis[f] = vis[fa[f]] = vis[fa[v]] = vis[fa[fa[f]]] = vis[fa[fa[v]]] = 0;
			add(u), add(v), add(f), add(fa[f]), add(fa[v]), add(fa[fa[f]]), add(fa[fa[v]]);
			vis[u] = vis[v] = vis[f] = vis[fa[f]] = vis[fa[v]] = vis[fa[fa[f]]] = vis[fa[fa[v]]] = 0;
			insert(u), insert(v), insert(f), insert(fa[f]), insert(fa[fa[f]]), insert(fa[v]), insert(fa[fa[v]]);
		}
	}
	return 0;
}
