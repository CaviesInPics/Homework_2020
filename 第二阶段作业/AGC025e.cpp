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

const int MAXN = 2005;
vector<int> linker[MAXN];
int n, m, w[MAXN], fa[MAXN], dep[MAXN], st[MAXN], ed[MAXN], foo[MAXN];

void dfs(int x)
{
	dep[x] = dep[fa[x]] + 1;
	for (int cur : linker[x])
		if (cur != fa[x]) fa[cur] = x, dfs(cur);
}

void operate(int u, int v)
{
	while (u != v)
	{
		if (dep[u] < dep[v]) swap(u, v);
		w[u] ++, u = fa[u]; 
	}
}

struct node
{
	int u, v, id;
	node() {}
	node(int u, int v, int id): u(u), v(v), id(id) {}
	void set() {u = v = 0;}
};

vector<node> route;

int ans[MAXN];

void Solve(int x)
{
	if (w[x] == 0) return;
	if (w[x] == 1)
	{
		for (auto &cur : route)
		{
			if (cur.u == x)
			{
				if (cur.v == fa[x])
				{
					ans[cur.id] = 1;
					cur.set;
				}
			}
		}
	}
	else
	{
		for (auto &cur : route)
	}
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i < n; i ++)
	{
		int u = read(), v = read();
		linker[u].push_back(v);
		linker[v].push_back(u);
	}
	dfs(1);
	for (int i = 1; i <= m; i ++)
	{
		int u = read(), v = read();
		if (operate(u, v)) st[i] = u, ed[i] = v;
		else st[i] = v, ed[i] = u;
	}
	int ans = 0;
	for (int i = 2; i <= n; i ++)
		ans += min(w[i], 2);
	cout << ans << endl;
	return 0;
}
