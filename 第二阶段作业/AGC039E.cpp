#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, a[55][55]; ll f[55][55][55];
char opt[55];

int main()
{
	cin >> n, n <<= 1;
	for (int i = 1; i <= n; i ++)
	{
		scanf("%s", opt + 1);
		for (int j = 1; j <= n; j ++)
			a[i][j] = opt[j] == '1';
	}

	for (int i = 2; i <= n; i ++) f[i][i][i] = 1;
	for (int len = 2; len <= n; len ++)
		for (int l = 2; l <= n - len + 1; l ++)
		{
			int r = l + len - 1;
			for (int pos = l + 1; pos < r; pos ++)
			{
				for (int i = l; i < pos; i ++)
					for (int j = pos + 1; j <= r; j ++)
						if (a[i][j])
						{
							for (int p = i; p < pos; p ++)
								for (int q = pos + 1; q <= j; q ++)
									f[l][r][pos] += f[l][p][i] * f[p + 1][q - 1][pos] * f[q][r][j];
						}
			}
		}

	ll ans = 0;
	for (int i = 2; i <= n; i ++)
		if (a[1][i]) ans += f[2][n][i];
	
	cout << ans << endl;
	return 0;
}