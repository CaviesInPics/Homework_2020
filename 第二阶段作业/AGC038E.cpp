#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read()
{
	int x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
	while (isdigit(c)) {x = x * 10 + c - '0', c = getchar();}
	return x * f;
}

const int mod = 998244353;
inline int inc(int x, int y) {x += y; return x >= mod ? x - mod : x;}
inline void add(int &x, int y) {y += x; x = y >= mod ? y - mod : y;}
inline int mul(int x, int y) {return (ll)x * y % mod;}
inline int qpow(int x, int y)
{
	int res = 1;
	for (; y; y >>= 1, x = mul(x, x))
		if (y & 1) res = mul(res, x);
	return res;
}

int n, a[405], b[405], f[405][405][405], fac[405], ifac[405];

int main()
{
	fac[0] = 1;
	for (int i = 1; i <= 400; i ++) fac[i] = mul(fac[i - 1], i);
	ifac[400] = qpow(fac[400], mod - 2);
	for (int i = 400; i >= 1; i --) ifac[i - 1] = mul(ifac[i], i);
	n = read(); int sa = 0, sb = 0;
	for (int i = 1; i <= n; i ++) sa += a[i] = read(), sb += b[i] = read();
	f[0][0][0] = 1;
	for (int i = 0; i < n; i ++)
		for (int j = 0; j <= 400; j ++)
			for (int k = 0; k <= 400; k ++) if (f[i][j][k])
			{
				int now = f[i][j][k]; add(f[i + 1][j][k], now);
				for (int cnt = 0, w = 1; cnt < b[i + 1]; cnt ++, w = mul(w, a[i + 1]))
					add(f[i + 1][j + a[i + 1]][k + cnt], mul(mul(now, mul(w, ifac[cnt])), mod - 1));
			}
	int ans = 0;
	for (int i = 1; i <= 400; i ++)
		for (int j = 0; j <= 400; j ++) if (f[n][i][j])
		{
			int now = f[n][i][j];
			add(ans, mul(now, mul(fac[j], qpow(qpow(i, mod - 2), j + 1))));
		}
	ans = mod - ans;
	printf("%d\n", mul(ans, sa));
	return 0;
}
