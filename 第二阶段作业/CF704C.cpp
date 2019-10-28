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
inline int inv(int x) {return qpow(x, MOD - 2);}

const int MAXN = 1e5 + 10;

struct edge
{
	int nxt, to, w;
	edge() {}
	edge(int nxt, int to, int w): nxt(nxt), to(to), w(w) {} 
} e[MAXN << 2];

int n, m, last[MAXN], cnt = 1, dp[MAXN][2][2], w[MAXN][2], once[MAXN][2], deg[MAXN];
bool vis[MAXN], iscycle; vector<int> top, cycle, value;
inline void addedge(int u, int v, int w) {e[++ cnt] = edge(last[u], v, w), last[u] = cnt, ++ deg[v];}

void dfs(int x, int pre)
{
//	printf("x = %d pre = %d\n", x, pre);
	vis[x] = 1, cycle.push_back(x);
	for (int i = last[x]; i; i = e[i].nxt)
	{
		if ((i ^ 1) == pre) continue;
		int v = e[i].to;
		value.push_back(e[i].w);
		if (!vis[v]) dfs(v, i);
		else
		{
			iscycle = 1;
			return;
		}
	}
}

void dfs2(int x, int pre)
{
	cycle.push_back(x);
	for (int i = last[x]; i; i = e[i].nxt)
	{
		if ((i ^ 1) == pre) continue;
		int v = e[i].to;
		value.push_back(e[i].w);
		dfs2(v, i);
	}
}

typedef pair<int, int> mypair;

mypair decode(int u, int v, int w)
{
	int col1, col2;
	if (u > v) col1 = (w >> 1) & 1, col2 = w & 1;
	else col1 = w & 1, col2 = (w >> 1) & 1;
	return mypair(col1, col2);
}

int main()
{
//	freopen("input.txt", "r", stdin);
	m = read(), n = read();
	for (int i = 1; i <= m; i ++)
	{
		int k = read();
		if (k == 1)
		{
			int u = read();
			if (u > 0) once[u][0] ++;
			else once[-u][1] ++;
		}
		else
		{
			int u = read(), v = read(), w = 0;
			if (abs(u) == abs(v))
			{
				if (u * v < 0)
				{
					u = abs(u);
					vis[u] = 1;
					top.push_back(u);
					::w[u][1] = 2;
					::w[u][0] = 0;
				}
				else
				{
					printf("%d\n", qpow(2, n - 1));
					return 0;
				}
			}
			if (abs(u) > abs(v)) swap(u, v);
			if (u < 0) w ++, u = -u;
			if (v < 0) w += 2, v = -v;
			addedge(u, v, w);
			addedge(v, u, w);
		}
	}
	
	for (int i = 1; i <= n; i ++)
		if (!last[i] && once[i][0] + once[i][1] == 1)
			return printf("%d\n", qpow(2, n - 1)), 0;
	
	for (int i = 1; i <= n; i ++) if (!vis[i] && (once[i][0] || once[i][1] || deg[i]))
	{
		top.emplace_back(i);
		cycle.clear(), value.clear(), iscycle = 0;
		dfs(i, 0);
		if (iscycle) // Solve Cycle
		{
			int len = cycle.size();
			for (int st = 0; st < 2; st ++)
			{
				for (int i = 0; i <= len + 1; i ++)	
					dp[i][0][0] = dp[i][0][1] = dp[i][1][0] = dp[i][1][1] = 0;
				dp[0][0][st] = 1;
				for (int i = 1; i < len; i ++)
					for (int a = 0; a < 2; a ++)
						for (int b = 0; b < 2; b ++)
							if (dp[i - 1][a][b])
							{
								int now = dp[i - 1][a][b], w = value[i - 1];
								mypair nw = decode(cycle[i - 1], cycle[i], w);
								int col1 = nw.first, col2 = nw.second;
								for (int c = 0; c < 2; c ++)
								{
									int nxt = a ^ ((b ^ col1) | (c ^ col2));
									add(dp[i][nxt][c], now);
								}
							}
				for (int a = 0; a < 2; a ++)
					for (int b = 0; b < 2; b ++)
						if (dp[len - 1][a][b])
						{
							int now = dp[len - 1][a][b];
							mypair nw = decode(cycle[0], cycle[len - 1], value[len - 1]);
							int col1 = nw.first, col2 = nw.second;
							int nxt = a ^ ((st ^ col1) | (b ^ col2));
							add(w[cycle[0]][nxt], now);
						}
			}
		}
		else // Solve Chain
		{
			int qaq = 0;
			for (int cur : cycle)
				if (deg[cur] == 1)
				{
					qaq = cur;
					break;
				}
			cycle.clear();
			value.clear();
			dfs2(qaq, 0);
			int len = cycle.size();
			for (int st = 0; st < 2; st ++)
			{
				for (int j = 0; j <= len + 1; j ++)	
					dp[j][0][0] = dp[j][0][1] = dp[j][1][0] = dp[j][1][1] = 0;
				dp[0][0][st] = 1;
				for (int j = 1; j < len; j ++)
					for (int a = 0; a < 2; a ++)
						for (int b = 0; b < 2; b ++)
							if (dp[j - 1][a][b])
							{
//								printf("%d %d %d\n", j, a, b); rua;
								int now = dp[j - 1][a][b], w = value[j - 1];
								mypair nw = decode(cycle[j - 1], cycle[j], w);
								int col1 = nw.first, col2 = nw.second;
//				printf("%d %d %d %d %d %d %d\n", j, a, b, dp[3][0][0], dp[3][0][1], dp[3][1][0], dp[3][1][1]);
								for (int c = 0; c < 2; c ++)
								{
									int nxt = a ^ ((b ^ col1) | (c ^ col2));
//									printf("j = %d %d %d\n", j, nxt, c);
									add(dp[j][nxt][c], now);
								}
//				printf("%d %d %d %d %d %d %d\n", j, a, b, dp[3][0][0], dp[3][0][1], dp[3][1][0], dp[3][1][1]);rua;
							}
//				printf("%d %d %d %d\n", dp[4][0][0], dp[4][0][1], dp[4][1][0], dp[4][1][1]);
				for (int a = 0; a < 2; a ++)
					for (int b = 0; b < 2; b ++)
						if (dp[len - 1][a][b])
						{
							int nxt = a;
							if (once[cycle.back()][0]) nxt ^= b;
							else if (once[cycle.back()][1]) nxt ^= b ^ 1;
							if (once[qaq][0]) nxt ^= st;
							else if (once[qaq][1]) nxt ^= st ^ 1;
							add(w[i][nxt], dp[len - 1][a][b]);
						}
			}
//			cerr << i << " " << w[i][0] << " " << w[i][1] << endl;
		}
	}
	
	static int f[2];
	f[0] = 1, f[1] = 0;
	
	for (int cur : top)
	{
		static int tmp[2];
		tmp[0] = f[0], tmp[1] = f[1];
		f[0] = f[1] = 0;
//		cerr << w[cur][0] << " " << w[cur][1] << endl; rua;
		for (int i = 0; i < 2; i ++)
			for (int j = 0; j < 2; j ++)
				add(f[i ^ j], mul(tmp[i], w[cur][j]));
	}
	int ans = 0;
	for (int i = 1; i <= n; i ++)
		if (!last[i] && !once[i][0] && !once[i][1])
			ans ++;
	ans = mul(qpow(2, ans), f[1]);
	printf("%d\n", ans);
	return 0;
}
