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

const int MAXN = 1005;
const int MAXM = 2e5 + 10;

typedef pair<int, int> mypair;

vector<int> linker[MAXN];
int n, m, vis[MAXN], from[MAXM], to[MAXM];
bool g1[MAXN][MAXN], g2[MAXN][MAXN];
mypair pre[MAXN];

void dfs1(int x)
{
	vis[x] = 1;
	for (int i = 0; i < linker[x].size(); i ++)
	{
		int cur = linker[x][i];
		if (vis[cur]) continue;
		pre[cur] = mypair(x, i), dfs1(cur);
	}
}

void dfs2(int x)
{
	vis[x] = 1;
	for (int i = linker[x].size() - 1; i >= 0; i --)
	{
		int cur = linker[x][i];
		if (vis[cur]) continue;
		pre[cur] = mypair(x, i), dfs2(cur);
	}
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; i ++)
	{
		from[i] = read(), to[i] = read();
		linker[from[i]].push_back(to[i]);
	}
	for (int s = 1; s <= n; s ++)
	{
		memset(vis, 0, sizeof vis);
		static mypair tmp[MAXN];
		dfs1(s);
		memcpy(tmp, pre, sizeof pre);
		memset(vis, 0, sizeof vis);
		dfs2(s);
		for (int i = 1; i <= n; i ++)
		{
			if (vis[i])
			{
				g1[s][i] = 1;
				if (pre[i].first != s || tmp[i].first != s)
					g2[s][i] = 1;
			}
		}
	}
	for (int i = 1; i <= m; i ++)
	{
		int u = from[i], v = to[i];
		if (g1[v][u] ^ g2[u][v]) puts("diff");
		else puts("same");
	}
	return 0;
}
