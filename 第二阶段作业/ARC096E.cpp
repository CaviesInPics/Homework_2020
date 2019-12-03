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

const int MAXN = 3005;
int n, MOD, s[MAXN][MAXN], pw[MAXN * MAXN], pww[MAXN], c[MAXN][MAXN];

inline int qpow(int x, int y)
{
	int res = 1;
	for (; y; y >>= 1, x = 1LL * x * x % MOD)
		if (y & 1) res = 1LL * res * x % MOD;
	return res;
}

int main()
{
	cin >> n >> MOD;
	for (int i = 0; i <= n; i ++) c[i][0] = 1;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= i; j ++)
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
	s[0][0] = 1;
	for (int i = 1; i <= n + 1; i ++)
		for (int j = 1; j <= i; j ++)
			s[i][j] = (1LL * s[i - 1][j] * j + s[i - 1][j - 1]) % MOD;
	pw[0] = 1;
	for (int i = 1; i <= n; i ++) pw[i] = (pw[i - 1] + pw[i - 1]) % (MOD - 1);
	for (int i = 0; i <= n; i ++) pww[i] = qpow(2, pw[i]);
	pw[0] = 1;
	for (int i = 1; i <= n * n; i ++) pw[i] = (pw[i - 1] + pw[i - 1]) % MOD;
	int ans = 0;
	for (int i = 0; i <= n; i ++)
	{
		int now = 0;
		for (int j = 0; j <= i; j ++)
			now = (now + 1LL * s[i + 1][j + 1] * pw[(n - i) * j] % MOD * pww[n - i]) % MOD;
		now = 1LL * now * c[n][i] % MOD;
		if (i & 1) ans = (ans - now) % MOD;
		else ans = (ans + now) % MOD;
	}
	ans = (ans + MOD) % MOD;
	cout << ans << endl;
	return 0;
}
