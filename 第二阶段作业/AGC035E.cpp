#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 155;
int k, n, mod, f[maxn][maxn][maxn], g[maxn][maxn];
inline void add(int &x, int y) {y += x; x = y >= mod ? y - mod : y;}

int main()
{
	// freopen("input.txt", "r", stdin);
	cin >> n >> k >> mod;
	if (n == 1) return puts("2"), 0;
	if (!(k & 1))
	{
		memset(g, 0, sizeof g);
		g[1][0] = 1, g[2][0] = 1;
		for (int i = 1; i <= n; i ++)
		{
			for (int j = 0; j <= k / 2; j ++) if (g[i][j])
				add(g[i + 2][j + 1], g[i][j]), add(g[i + 2][0], g[i][j]);
		}
		int ans = 0, res = 0;
		for (int i = 0; i <= k / 2; i ++)
			add(ans, g[n + 1][i]);
		for (int i = 0; i <= k / 2; i ++)
			add(res, g[n + 2][i]);
		ans = 1ll * ans * res % mod;
		cout << ans << endl;
	}
	else
	{
		memset(f, 0, sizeof f);
		int lst = 2;
		f[lst][0][0] = 1;
		for (int i = lst; i <= (k - 1); i += 2, lst = i)
			for (int j = 0; j <= k + 1; j ++)
				for (int l = 0; l <= n; l ++)
					if (f[i][j][l])
					{
						int now = f[i][j][l];
						add(f[i + 2][0][0], now);
						add(f[i + 2][0][l + 1], now);
					}
		for (int i = lst; i <= n; i += 2, lst = i)
		{
			for (int j = 0; j <= k + 1; j ++)
				for (int l = 0; l <= n; l ++)
					if (f[i][j][l])
					{
						int now = f[i][j][l];
						add(f[i + 2][0][0], now);
						add(f[i + 2][j ? j + 1 : 0][0], now); // 必须要有一条横着的边
						add(f[i + 2][0][l + 1], now);
						add(f[i + 2][max(j + 1, l + 2)][l + 1], now);
					}
		}
		memcpy(f[lst - k], f[lst], sizeof f[lst]);
		lst = lst - k;
		for (int i = lst; i <= n; i += 2, lst = i)
		{
			for (int j = 0; j <= k + 1; j ++)
				for (int l = 0; l <= n; l ++)
					if (f[i][j][l])
					{
						int now = f[i][j][l];
						add(f[i + 2][0][0], now);
						add(f[i + 2][j ? j + 1 : 0][0], now);
					}
		}
		int ans = 0;
		for (int j = 0; j <= k + 1; j ++)
			for (int l = 0; l <= n; l ++)
				add(ans, f[lst][j][l]);
		cout << ans << endl;
	}
}