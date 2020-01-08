#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;

inline int inc(int x, int y) {x += y; return x >= mod ? x - mod : x;}

inline int qpow(int x, int y)
{
	int res = 1;
	for (; y; y >>= 1, x = 1ll * x * x % mod)
		if (y & 1) res = 1ll * res * x % mod;
	return res;
}

const int inv3 = (mod + 1) / 3;

int n, inv[1000005], ans = 0;

int main()
{
	cin >> n;
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= n; i ++)
		inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
	for (int i = 1, w = inv3; i <= n; i ++, w = 1ll * w * inv3 % mod)
	{
		ans = inc(ans, 1ll * w * inv[n] % mod * inv[n - i + 1] % mod);
	}
	cout << ans << endl;
	return 0;
}