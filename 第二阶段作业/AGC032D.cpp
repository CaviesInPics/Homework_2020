#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const int maxn = 5005;
int n, a, b, p[maxn];
ll f[maxn][maxn];

int main()
{
	scanf("%d%d%d", &n, &a, &b);
	for (int i = 1; i <= n; i ++)
		scanf("%d",  p + i);
	memset(f, 0x3f, sizeof f);
	f[0][0] = 0;
	for (int i = 1; i <= n; i ++)
		for (int j = 0; j <= n; j ++)
		{
			if (p[i] > j) f[i][j] = min(f[i][j], f[i - 1][j] + a), f[i][p[i]] = min(f[i][p[i]], f[i - 1][j]);
			else f[i][j] = min(f[i][j], f[i - 1][j] + b);
		}
	ll ans = inf;
	for (int i = 0; i <= n; i ++) ans = min(ans, f[n][i]);
	printf("%lld\n", ans);
	return 0;
}