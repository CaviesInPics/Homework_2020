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
 
const int MAXN = 1e5 + 10;
struct edge
{
	int nxt, to, w;
	edge() {}
	edge(int nxt, int to, int w): nxt(nxt), to(to), w(w) {}
} e[MAXN << 1];
 
int n, cnt, last[MAXN], rt, dis[MAXN];
 
inline void addedge(int u, int v, int w) {e[++ cnt] = edge(last[u], v, w), last[u] = cnt;}
 
void findrt(int x, int fa)
{
	if (dis[x] >= dis[rt]) rt = x;
	for (int i = last[x]; i; i = e[i].nxt)
	{
		int v = e[i].to;
		if (v == fa) continue;
		dis[v] = dis[x] + e[i].w;
		findrt(v, x);
	}
}
 
namespace t1
{
 
int top[MAXN], dis[MAXN], mxdis[MAXN], wson[MAXN], leaf_cnt, root, rnk[MAXN], fa[MAXN], sum[MAXN], pnt[MAXN][17];
vector<int> leaf;
 
void dfs(int x)
{
	mxdis[x] = dis[x];
	pnt[x][0] = fa[x];
	for (int i = 1; i < 17; i ++)
		pnt[x][i] = pnt[pnt[x][i - 1]][i - 1];
	for (int i = last[x]; i; i = e[i].nxt)
	{
		int v = e[i].to;
		if (v == fa[x]) continue;
		fa[v] = x, dis[v] = dis[x] + e[i].w;
		dfs(v);
		if (mxdis[v] > mxdis[wson[x]])
			wson[x] = v;
	}
	if (wson[x]) mxdis[x] = mxdis[wson[x]];
}
 
void dfs2(int x, int chain)
{
	top[x] = chain;
	if (wson[x])
	{
		dfs2(wson[x], chain);
		for (int i = last[x]; i; i = e[i].nxt)
		{
			int v = e[i].to;
			if (v == fa[x] || v == wson[x]) continue;
			dfs2(v, v);
		}
	}
	else leaf.push_back(x);
}
 
inline bool cmp(const int &a, const int &b)
{
	return dis[a] - dis[fa[top[a]]] > dis[b] - dis[fa[top[b]]];
}
 
inline void init()
{
	dfs(root), dfs2(root, root);
	sort(leaf.begin(), leaf.end(), cmp);
	for (int i = 0; i < leaf.size(); i ++)
	{
		int cur = leaf[i];
		rnk[top[cur]] = i + 1, sum[i + 1] = sum[i] + dis[cur] - dis[fa[top[cur]]];
	}
}
 
inline int Solve(int x, int y)
{
	y = min((int)leaf.size(), 2 * y - 1);
	if (y >= rnk[top[x]]) return sum[y];
	int now = x;
	for (int i = 16; i >= 0; i --)
		if (rnk[top[pnt[now][i]]] > y)
			now = pnt[now][i];
	now = fa[now];
	return max(sum[y - 1], sum[y] - (mxdis[now] - dis[now])) + mxdis[x] - dis[now];
}
 
}
 
namespace t2
{
 
int top[MAXN], dis[MAXN], mxdis[MAXN], wson[MAXN], leaf_cnt, root, rnk[MAXN], fa[MAXN], sum[MAXN], pnt[MAXN][17];
vector<int> leaf;
 
void dfs(int x)
{
	mxdis[x] = dis[x];
	pnt[x][0] = fa[x];
	for (int i = 1; i < 17; i ++)
		pnt[x][i] = pnt[pnt[x][i - 1]][i - 1];
	for (int i = last[x]; i; i = e[i].nxt)
	{
		int v = e[i].to;
		if (v == fa[x]) continue;
		fa[v] = x, dis[v] = dis[x] + e[i].w;
		dfs(v);
		if (mxdis[v] > mxdis[wson[x]])
			wson[x] = v;
	}
	if (wson[x]) mxdis[x] = mxdis[wson[x]];
}
 
void dfs2(int x, int chain)
{
	top[x] = chain;
	if (wson[x])
	{
		dfs2(wson[x], chain);
		for (int i = last[x]; i; i = e[i].nxt)
		{
			int v = e[i].to;
			if (v == fa[x] || v == wson[x]) continue;
			dfs2(v, v);
		}
	}
	else leaf.push_back(x);
}
 
inline bool cmp(const int &a, const int &b)
{
	return dis[a] - dis[fa[top[a]]] > dis[b] - dis[fa[top[b]]];
}
 
inline void init()
{
	dfs(root), dfs2(root, root);
	sort(leaf.begin(), leaf.end(), cmp);
	for (int i = 0; i < leaf.size(); i ++)
	{
		int cur = leaf[i];
		rnk[top[cur]] = i + 1, sum[i + 1] = sum[i] + dis[cur] - dis[fa[top[cur]]];
	}
}
 
inline int Solve(int x, int y)
{
	y = min((int)leaf.size(), 2 * y - 1);
	if (y >= rnk[top[x]]) return sum[y];
	int now = x;
	for (int i = 16; i >= 0; i --)
		if (rnk[top[pnt[now][i]]] > y)
			now = pnt[now][i];
	now = fa[now];
	return max(sum[y - 1], sum[y] - (mxdis[now] - dis[now])) + mxdis[x] - dis[now];
}
 
}
 
int main()
{
	n = read(); int m = read();
	for (int i = 1; i < n; i ++)
	{
		int u = read(), v = read(), w = read();
		addedge(u, v, w), addedge(v, u, w);
	}
	findrt(1, 0), t1::root = rt, dis[rt] = 0, findrt(rt, 0), t2::root = rt;
//	printf("root: %d %d\n", t1::root, t2::root);
	t1::init(), t2::init();
	int lastans = 0;
	for (int i = 1; i <= m; i ++)
	{
		int x = read(), y = read();
		x = (x + lastans - 1) % n + 1;
		y = (y + lastans - 1) % n + 1;
//		if (i == 2) printf("(%d, %d)\n", x, y);
		printf("%d\n", lastans = max(t1::Solve(x, y), t2::Solve(x, y)));
	}
	return  0;
}
