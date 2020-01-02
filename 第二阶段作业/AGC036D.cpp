#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll inf = 1ll << 60;

int n, a[505][505];
ll s1[505][505], s2[505][505], f[505][505];

inline ll sum1(int l1, int r1, int l2, int r2)
{
	if (l1 > r1 || l2 > r2) return 0;
	return s1[r1][r2] - s1[l1-1][r2] - s1[r1][l2-1] + s1[l1-1][l2-1];
}

inline ll sum2(int l1, int r1, int l2, int r2)
{
	if (l1 > r1 || l2 > r2) return 0;
	return s2[r1][r2] - s2[l1-1][r2] - s2[r1][l2-1] + s2[l1-1][l2-1];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			if (i != j) cin >> a[i][j];
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			s1[i][j] = (i < j ? a[i][j] : 0) + s1[i - 1][j] + s1[i][j - 1] - s1[i - 1][j - 1];
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			s2[i][j] = (i < j ? 0 : a[i][j]) + s2[i - 1][j] + s2[i][j - 1] - s2[i - 1][j - 1];
	memset(f, 0x3f, sizeof f);
	f[0][0] = 0;
	for (int i = 1; i <= n; i ++)
		f[i][0] = s1[i][i];
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j < i; j ++)
			for (int k = 0; k < j; k ++)
			{
				ll res = f[j][k];
				res += sum1(j + 1, i, j + 1, i);
				res += sum2(j + 1, i, 1, k);
				f[i][j] = min(f[i][j], res);
			}
	ll ans = inf;
	for (int i = 0; i < n; i ++) ans = min(ans, f[n][i]);
	cout << ans << endl;
	return 0;
}