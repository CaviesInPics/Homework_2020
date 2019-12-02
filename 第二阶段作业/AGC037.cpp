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

const int MAXN = 105;
int n, m, A[MAXN][MAXN], B[MAXN][MAXN], C[MAXN][MAXN];

int match[MAXN], t[MAXN];
bool vis[MAXN], mark[MAXN][MAXN];
bool g[MAXN][MAXN];

bool find(int x)
{
	for (int i = 1; i <= n; i ++) if (g[x][i] && !vis[i])
	{
		vis[i] = 1;
		if (!match[i] || find(match[i]))
		{
			t[x] = i, match[i] = x;
			return 1;
		}
	}
	return 0;
}

void Augment()
{
	for (int i = 1; i <= n; i ++)
		if (!t[i]) memset(vis, 0, sizeof vis), find(i); // cerr << t[i] << endl;
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			A[i][j] = read();
	for (int i = 1; i <= m; i ++)
	{
		memset(t, 0, sizeof t);
		memset(g, 0, sizeof g);
		memset(match, 0, sizeof match);
		for (int j = 1; j <= m; j ++)
			for (int k = 1; k <= n; k ++)
				if (!mark[k][j]) g[k][(A[k][j] - 1) / m + 1] = 1;
		Augment();
//		for (int j = 1; j <= n; j ++)
//			printf("%d ", t[j]); puts("");
		for (int j = 1; j <= n; j ++)
		{
			int col = t[j];
			for (int k = 1; k <= m; k ++)
				if (!mark[j][k] && ((A[j][k] - 1) / m + 1) == col)
				{
					mark[j][k] = 1;
					B[j][i] = A[j][k];
					break;
				}
		}
	}
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			printf("%d%c", B[i][j], j == m ? 10 : 32);
	for (int i = 1; i <= m; i ++)	
		for (int j = 1; j <= n; j ++)
			for (int k = 2; k <= n; k ++)
				if (B[k - 1][i] > B[k][i]) swap(B[k - 1][i], B[k][i]);
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			printf("%d%c", B[i][j], j == m ? 10 : 32);
	return 0;
}
