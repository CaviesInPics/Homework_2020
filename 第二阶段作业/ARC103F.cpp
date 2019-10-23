#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read()
{
	ll x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
	while (isdigit(c)) {x = x * 10 + c - '0', c = getchar();}
	return x * f;
}

const int MAXN = 1e5 + 10;
int n, seq[MAXN], sz[MAXN], root;
vector<int> linker[MAXN];
ll D[MAXN], f[MAXN], g[MAXN];

inline bool cmp(const int &a, const int &b) {return D[a] < D[b];}

void dfs(int x, int fa)
{
	f[x] = 0;
	for (int i = 0; i < linker[x].size(); i ++)
	{
		int cur = linker[x][i];
		if (cur == fa) continue;
		dfs(cur, x), f[x] += f[cur] + sz[cur];
	}
}

void dfs2(int x, int fa)
{
	if (x == root) g[x] = 0;
	else g[x] = g[fa] + n - sz[x] + f[fa] - f[x] - sz[x];
	for (int i = 0; i < linker[x].size(); i ++)
	{
		int cur = linker[x][i];
		if (cur == fa) continue;
		dfs2(cur, x);
	}
}

inline bool check()
{
	dfs(root, 0), dfs2(root, 0);
//	for (int i = 1; i <= n; i ++)
//		printf("(%d, %d), ", f[i], g[i]);
//	puts("");
	for (int i = 1; i <= n; i ++)
		if (f[i] + g[i] != D[i]) return 0;
	return 1;
}

int main()
{
//	freopen("input.txt", "r", stdin);
	n = read();
	for (int i = 1; i <= n; i ++) D[i] = read(), seq[i] = i, sz[i] = 1;
	sort(seq + 1, seq + 1 + n, cmp), root = seq[1];
	for (int i = n; i > 1; i --)
	{
		int now = seq[i];
		int l = 1, r = i - 1, pos = -1;
		ll need = D[now] + 2 * sz[now] - n;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			if (D[seq[mid]] == need)
			{
				pos = seq[mid];
				break;
			}
			else if (D[seq[mid]] > need) r = mid - 1;
			else l = mid + 1;
		}
//		printf("%d (%d, %d, %d, %d)\n", i, now, pos, sz[now], need);
		if (pos == -1) return puts("-1"), 0;
		linker[pos].push_back(now), sz[pos] += sz[now];
	}
	if (check())
	{
		for (int i = 1; i <= n; i ++)
		{
			for (int j = 0; j < linker[i].size(); j ++)
			{
				int to = linker[i][j];
				printf("%d %d\n", i, to);
			}
		}
	}
	else puts("-1");
	return 0;
}
