#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
const int maxm = 4e5 + 10;

struct edge
{
	int nxt, to;
	edge() {}
	edge(int nxt, int to): nxt(nxt), to(to) {}
} e[maxm << 1];

typedef pair<int, int> mypair;
int n, m, last[maxn], cnt = 1;
int deg[maxn], st[maxm], top;
bool vis[maxm << 1];
vector<mypair> ans;

inline void addedge(int u, int v) {e[++ cnt] = edge(last[u], v), last[u] = cnt;}

void dfs(int x)
{
	for (int &i = last[x]; i; i = e[i].nxt) if (!vis[i])
	{
		int v = e[i].to;
		vis[i] = vis[i ^ 1] = 1;
		int _ = i;
		dfs(v);
		st[++ top] = _;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= m; i ++)
	{
		int u, v; cin >> u >> v;
		addedge(u, v), deg[u] ++;
		addedge(v, u), deg[v] ++;
	}
	vector<int> foo(0);
	for (int i = 1; i <= n; i ++)
		if (deg[i] & 1) foo.push_back(i);
	for (int i = 0; i < foo.size(); i += 2)
		addedge(foo[i], foo[i + 1]), deg[foo[i]] ++,
		addedge(foo[i + 1], foo[i]), deg[foo[i + 1]] ++;
	if ((cnt - 1) & 3) addedge(1, 1), addedge(1, 1), deg[1] += 2;
	dfs(1);
	for (int i = 1; i <= top; i ++)
	{
		int x = st[i];
		int u = e[x].to, v = e[x ^ 1].to;
		if (i & 1) swap(u, v);
		ans.emplace_back(u, v);
	}
	printf("%d\n", ans.size());
	for (auto cur : ans)
		printf("%d %d\n", cur.first, cur.second);
	return 0;
}