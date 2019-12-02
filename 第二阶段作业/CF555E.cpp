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

const int MAXN = 2e5 + 10;
struct edge
{
	int nxt, to;
	edge() {}
	edge(int nxt, int to): nxt(nxt), to(to) {}
} e[MAXN << 1]; 
vector<int> linker[MAXN];
int n, m, q, s[MAXN], d[MAXN], last[MAXN], cnt = 1;
inline void addedge(int u, int v) {e[++ cnt] = edge(last[u], v), last[u] = cnt;}

int dfn[MAXN], low[MAXN], ind, st[MAXN], top, bel[MAXN], bcc;
bool vis[MAXN];
void tarjan(int x, int pre)
{
	dfn[x] = low[x] = ++ ind;
	st[++ top] = x;
	for (int i = last[x]; i; i = e[i].nxt)
	{
		int v = e[i].to;
		if (!dfn[v]) tarjan(v, i), low[x] = min(low[x], low[v]);
		else if ((i ^ 1) != pre) low[x] = min(low[x], dfn[v]);
	}
	if (pre && low[x] > dfn[e[pre ^ 1].to])
	{
		int now = -1;
		bcc ++;
		while (now != x)
		{
			now = st[top --];
			bel[now] = bcc;
		}
	}
	else if (!pre)
	{
		int now = -1;
		bcc ++;
		while (now != x)
		{
			now = st[top --];
			bel[now] = bcc;
		}
	}
}

int fa[MAXN], dep[MAXN], f[MAXN][20];
void dfs(int x)
{
	vis[x] = 1, f[x][0] = fa[x], dep[x] = dep[fa[x]] + 1;
	for (int i = 1; i < 18; i ++) f[x][i] = f[f[x][i - 1]][i - 1];
	for (int cur : linker[x])
		if (cur != fa[x]) fa[cur] = x, dfs(cur);
}

typedef pair<int, int> mypair;
inline int lca(int x, int y)
{
	if (dep[x] < dep[y]) swap(x, y);
	if (dep[x] ^ dep[y])
		for (int i = 17; i >= 0; i --)
			if (dep[f[x][i]] >= dep[y]) x = f[x][i];
//	cerr << x << " " << y << " " << dep[x] << " " << dep[y] << " " << f[1][0] << endl;
	if (x == y) return x;
	for (int i = 17; i >= 0; i --)
		if (f[x][i] != f[y][i])
			x = f[x][i], y = f[y][i];
	return fa[x];
}

int bar[MAXN][2];
bool flag;

void check(int x, int pre)
{
	vis[x] = 1; 
	for (int cur : linker[x]) if (cur != pre)
		check(cur, x),
		bar[x][0] += bar[cur][0],
		bar[x][1] += bar[cur][1];
	if (bar[x][0] && bar[x][1])
	{
//		cerr << x << " " << pre << "  "<< bar[x][0] << " " << bar[x][1] << endl;
		flag = 0;
		return;
	}
}

int main()
{
	n = read(), m = read(), q = read();
	for (int i = 1; i <= m; i ++)
	{
		int u = read(), v = read();
		addedge(u, v), addedge(v, u);
	}
	for (int i = 1; i <= n; i ++)
		if (!dfn[i]) tarjan(i, 0);
	for (int x = 1; x <= n; x ++)
		for (int i = last[x]; i; i = e[i].nxt)
			if (bel[e[i].to] != bel[x])
				linker[bel[x]].push_back(bel[e[i].to]);
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= bcc; i ++) if (!vis[i]) dfs(i);
//	cerr << bcc << endl;
//	for (int i = 1; i <= n; i ++)
//		printf("%d ", bel[i]);
//	puts("");
	for (int i = 1; i <= q; i ++)
	{
		int s = read(), d = read();
		s = bel[s], d = bel[d];
		if (s == d) continue;
		int l = lca(s, d);
//		cerr <<"l="<<l<<" s="<<s<<" d="<<d<<endl;
		if (!l) {puts("No"); return 0;}
		bar[s][0] ++, bar[l][0] --, bar[d][1] ++, bar[l][1] --;
	}
	flag = 1;
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= bcc; i ++)
		if (!vis[i]) check(i, 0);
	if (flag) puts("Yes");
	else puts("No");
	return 0;
}
