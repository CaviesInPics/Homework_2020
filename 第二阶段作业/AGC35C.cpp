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
vector<int> linker[MAXN];
int n, w[MAXN], buc[MAXN];

inline void addedge(int u, int v)
{
	linker[u].push_back(v);
	linker[v].push_back(u);
}

bool dfs(int x, int fa)
{
	w[x] = w[fa] ^ (x % n);
	if (buc[w[x] ^ n ^ 1])
	{
		addedge(n, x), addedge(buc[w[x] ^ n ^ 1], n << 1);
		return 1;
	}
	buc[w[x]] = x;
	for (int cur : linker[x])
		if (cur != fa)
		{
			if (dfs(cur, x)) return 1;
		}
	return 0;
}

int main()
{
	n = read();
	if (n == 1 || n == 2) return puts("No"), 0;
	addedge(2, n + 1);
	for (int i = 2; i < n; i += 2)
	{
		addedge(i, i + 1);
		addedge(i + 1, 1);
		addedge(n + i, 1);
		addedge(n + i + 1, n + i);
	}
	if (!(n & 1))
	{
		if (!dfs(1, 0)) return puts("No"), 0;
	}
	puts("Yes");
	for (int x = 1; x <= n << 1; x ++)
		for (int cur : linker[x])
			if (cur > x) printf("%d %d\n", x, cur);
	return 0;
}
