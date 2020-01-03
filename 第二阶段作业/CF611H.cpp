#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

char opt[10];
int n, m, g[10][10], p[10][10];

inline int count(int x)
{
	int y = 0;
	while (x) y ++, x /= 10;
	return y;
}

typedef pair<int, int> mypair;
vector<mypair> ans;
vector<int> cnt[10];
int sp[10];

const int inf = 0x3f3f3f3f;

struct edge
{
	int nxt, to, w;
	edge() {}
	edge(int nxt, int to, int w): nxt(nxt), to(to), w(w) {}
} e[200005];

int S, T, last[100005], nn = 1, cur[100005], dis[100005];
inline void addedge(int u, int v, int w) {e[++ nn] = edge(last[u], v, w), last[u] = nn;}
inline void add(int u, int v, int w) {addedge(u, v, w), addedge(v, u, 0);}
inline bool bfs()
{
	static int q[100005];
	int head = 1, tail = 0;
	for (int i = 1; i <= T; i ++) dis[i] = inf;
	dis[q[++ tail] = S] = 0;
	while (head <= tail)
	{
		int x = q[head ++];
		for (int i = last[x]; i; i = e[i].nxt) if (e[i].w)
		{
			int v = e[i].to;
			if (dis[v] == inf) dis[q[++ tail] = v] = dis[x] + 1;
		}
	}
	return dis[T] < inf;
}
int aug(int x, int low)
{
	if (x == T || !low) return low;
	int res = 0, st;
	for (int &i = cur[x]; i; i = e[i].nxt)
	{
		int v = e[i].to;
		if (e[i].w && dis[v] == dis[x] + 1 && (st = aug(v, min(low, e[i].w))) > 0)
		{
			low -= st, res += st;
			e[i].w -= st, e[i ^ 1].w += st;
			if (!low) break;
		}
	}
	return res;
}
int dinic()
{
	int res = 0;
	while (bfs())
	{
		for (int i = 1; i <= T; i ++) cur[i] = last[i];
		res += aug(S, inf);
	}
	return res;
}
void clear()
{
	memset(last, 0, (nn + 1) << 2);
	nn = 1;
}

int fa[10];
int find(int x) {while (x != fa[x]) x = fa[x] = fa[fa[x]]; return x;}

bool check()
{
	for (int i = 1; i <= m; i ++) fa[i] = i;
	for (int i = 1; i <= m; i ++)
		for (int j = i + 1; j <= m; j ++) if (p[i][j])
		{
			int u = find(i), v = find(j);
			if (u == v) return 0;
			fa[u] = v;
		}
	return 1;
}

void dfs(int x, int y)
{
	if (x == m + 1)
	{
		clear();
		int ncnt = 0;
		for (int i = 1; i <= m; i ++)
			for (int j = i; j <= m; j ++)
				if (p[i][j]) ncnt ++;
		if (ncnt != m - 1) return;
		if (!check()) return;
		static int id[10][10];
		int ind = 0;
		memset(id, 0, sizeof id);
		S = m * m + m + 1, T = S + 1;
		int all = 0;
		for (int i = 1; i <= m; i ++)
			for (int j = i; j <= m; j ++)
			{
				add(S, id[i][j] = ++ ind, g[i][j] - p[i][j]);
				add(id[i][j], i + m * m, inf);
				if (i != j) add(id[i][j], j + m * m, inf);
			}
		for (int i = 1; i <= m; i ++)
			add(i + m * m, T, cnt[i].size()), all += cnt[i].size();
		// cerr << "ind = " << ind << endl;
		int flow = dinic();
		if (flow == all)
		{
			ans.clear();
			for (int i = 1; i <= m; i ++)
				for (int j = i + 1; j <= m; j ++)
					if (p[i][j]) ans.emplace_back(sp[i], sp[j]);
			for (int i = 1; i <= m; i ++)
				for (int j = i; j <= m; j ++)
				{
					int cur = id[i][j];
					for (int e_id = last[cur]; e_id; e_id = e[e_id].nxt)
					{
						int v = e[e_id].to;
						if (v == i + m * m)
						{
							for (int k = 1; k <= inf - e[e_id].w; k ++)
							{
								ans.emplace_back(sp[j], cnt[i].back());
								cnt[i].pop_back();
							}
						}
						else if (v == j + m * m && i != j)
						{
							for (int k = 1; k <= inf - e[e_id].w; k ++)
							{
								ans.emplace_back(sp[i], cnt[j].back());
								cnt[j].pop_back();
							}
						}
					}
				}
		}
		return;
	}
	if (y == m + 1) return dfs(x + 1, x + 2);
	bool flag = 0;
	for (int i = 1; i < x; i ++)
		if (p[i][x] && p[i][y])
		{
			flag = 1;
			break;
		}
	dfs(x, y + 1);
	if (ans.size()) return;
	if (!flag && g[x][y])
	{
		p[x][y] = 1;
		dfs(x, y + 1);
	}
	p[x][y] = 0;
}

int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d", &n); m = count(n);
	for (int i = 1; i <= n; i ++) cnt[count(i)].push_back(i);
	for (int i = 1; i < n; i ++)
	{
		int u, v;
		scanf("%s", opt), u = strlen(opt);
		scanf("%s", opt), v = strlen(opt);
		if (u > v) swap(u, v); g[u][v] ++;
	}
	for (int i = 1; i <= m; i ++)
		sp[i] = cnt[i].back(), cnt[i].pop_back();
	dfs(1, 2);
	if (ans.empty()) puts("-1");
	else
	{
		for (auto cur : ans)
			printf("%d %d\n", cur.first, cur.second);
	}
	return 0;
}