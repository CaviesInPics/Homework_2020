#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;
inline int inc(int x, int y) {y += x; return y >= MOD ? y - MOD : y;}

inline int qpow(int x, int y)
{
	int res = 1;
	for (; y; y >>= 1, x = 1LL * x * x % MOD)
		if (y & 1) res = 1LL * res * x % MOD;
	return res;
}

int n, k, fac[500005], ifac[500005];

inline int binom(int x, int y)
{
	if (y < 0 || y > x) return 0;
	return 1LL * fac[x] * ifac[y] % MOD * ifac[x - y] % MOD;
}

int main()
{
	fac[0] = ifac[0] = 1;
	for (int i = 1; i <= 5e5; i ++) fac[i] = 1LL * fac[i - 1] * i % MOD;
	ifac[500000] = qpow(fac[500000], MOD - 2);
	for (int i = 5e5; i >= 1; i --) ifac[i - 1] = 1LL * ifac[i] * i % MOD;
	cin >> n >> k;
	int ans = 0;
	for (int i = n; i <= k; i ++)
		ans = inc(ans, binom(k - 1, i - 1));
	cout << ans << endl;
	return 0;
}
