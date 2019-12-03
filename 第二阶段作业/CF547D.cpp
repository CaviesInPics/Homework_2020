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
int n, x[MAXN], y[MAXN], buc[MAXN], tot, col[MAXN], vis[MAXN];
vector<int> foo[MAXN], linker[MAXN];

void dfs(int x)
{
	vis[x] = 1;
	for (int cur : linker[x])
		if (!vis[cur])
			vis[cur] = 1, col[cur] = col[x] ^ 1, dfs(cur);
}

int main()
{
	n = read();
	for (int i = 1; i <= n; i ++)
		x[i] = read(), y[i] = read();
	for (int i = 1; i <= n; i ++) buc[i] = x[i];
	tot = unique(buc + 1, buc + 1 + n) - buc - 1;
	for (int i = 1; i <= n; i ++)
		x[i] = lower_bound(buc + 1, buc + 1 + tot, x[i]) - buc;
	for (int i = 1; i <= n; i ++) foo[x[i]].push_back(i);
	for (int i = 1; i <= tot; i ++)
		if (foo[i].size() >= 2)
		{
			int sz = foo[i].size() - 1;
			for (int j = 0; j < foo[i].size() / 2; j ++)
				linker[foo[i][j]].push_back(foo[i][sz - j]),
				linker[foo[i][sz - j]].push_back(foo[i][j]);
		}		
	for (int i = 1; i <= n; i ++) buc[i] = y[i];
	tot = unique(buc + 1, buc + 1 + n) - buc - 1;
	for (int i = 1; i <= n; i ++)
		y[i] = lower_bound(buc + 1, buc + 1 + tot, y[i]) - buc;
	for (int i = 1; i <= n; i ++) foo[i].clear();
	for (int i = 1; i <= n; i ++) foo[y[i]].push_back(i);
	for (int i = 1; i <= tot; i ++)
		if (foo[i].size() >= 2)
		{
			int sz = foo[i].size() - 1;
			for (int j = 0; j < foo[i].size() / 2; j ++)
				linker[foo[i][j]].push_back(foo[i][sz - j]),
				linker[foo[i][sz - j]].push_back(foo[i][j]);
		}
	for (int i = 1; i <= n; i ++)
		if (!vis[i]) dfs(i);
	for (int i = 1; i <= n; i ++)
		putchar(col[i] ? 'r' : 'b');
	puts("");
	return 0;
}
