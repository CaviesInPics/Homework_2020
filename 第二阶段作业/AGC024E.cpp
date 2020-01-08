#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int mod;
inline void add(int &x, int y) {y += x; x = y >= mod ? y - mod : y;}
int n, k, f[305][305][305];
int main()
{
	cin >> n >> k >> mod;
	f[0][1][0] = 1;
	for (int i = 0; i <= n; i ++)
		for (int j = 1; j <= k; j ++)
			for (int l = i; l >= 0; l --)
				if (f[i][j][l])
				{
					if (l) add(f[i][j][l - 1], f[i][j][l]); // 考虑在哪一次操作，每往前一个次能操作的位置就减少一个
					else add(f[i][j + 1][i], f[i][j][l]);
					add(f[i + 1][j][l], 1ll * f[i][j][l] * (l + 1) % mod);
				}
	printf("%d\n", f[n][k + 1][n]);
}