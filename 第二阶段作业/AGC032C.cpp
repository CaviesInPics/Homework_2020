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

const int MAXN = 1e5 + 10;

int n, m, deg[MAXN], cnt[MAXN];
vector<int> linker[MAXN];

bool vis[MAXN];
int S, T, num;

void dfs(int x)
{
	if (x == T)
	{
		num ++;
		return;
	}
	vis[x] = 1;
	for (int cur : linker[x])
		if (!vis[cur]) dfs(cur);
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; i ++)
	{
		int u = read(), v = read();
		linker[u].push_back(v), deg[u] ++;
		linker[v].push_back(u), deg[v] ++;
	}
	
	for (int i = 1; i <= n; i ++) cnt[deg[i]] ++;

	for (int i = 1; i <= n; i ++)
		if (deg[i] & 1) return puts("No"), 0;
		
	for (int i = 6; i <= m; i += 2)
		if (cnt[i]) return puts("Yes"), 0;

	if (cnt[4] >= 3) return puts("Yes"), 0;
	
	if (cnt[4] < 2) return puts("No"), 0;
	
	for (int i = 1; i <= n; i ++)
		if (deg[i] == 4)
		{
			if (!S) S = i;
			else T = i;
		}
	
	dfs(S);
	
	if (num == 2) puts("Yes");
	else puts("No");

	return 0;
}
