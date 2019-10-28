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

const int MOD = 1e9 + 7;
inline int inc(int x, int y) {x += y; return x >= MOD ? x - MOD : x;}
inline void add(int &x, int y) {y += x; x = y >= MOD ? y - MOD : y;}
inline int mul(int x, int y) {return (ll)x * y % MOD;}
inline int qpow(int x, int y)
{
	int res = 1;
	for (; y; y >>= 1, x = mul(x, x))
		if (y & 1) res = mul(res, x);
	return res;
}
inline int inv(int x) {return qpow(x, MOD - 2);}

const int MAXN = 1505;
const int MAXK = 1e5 + 10;

int n, m, fac[MAXK], ifac[MAXK], pw1[MAXK], pw2[MAXK], c[MAXN];
int sc[MAXN], h1[MAXN], h2[MAXN], ch1[MAXN], ch2[MAXN], g1[MAXN], g2[MAXN];

inline int binom(int x, int y)
{
	if (y < 0 || y > x) return 0;
	return mul(mul(fac[x], ifac[y]), ifac[x - y]);
}

int main()
{
	fac[0] = ifac[0] = 1;
	for (int i = 1; i <= 100000; i ++) fac[i] = mul(fac[i - 1], i);
	ifac[100000] = inv(fac[100000]);
	for (int i = 100000; i >= 2; i --) ifac[i - 1] = mul(ifac[i], i);
	n = read(), m = read();
	int a = read(), b = read(), p = mul(a, inv(b));
	int t = read();
	pw1[0] = pw2[0] = 1;
	for (int i = 1; i <= t; i ++)
	{
		pw1[i] = mul(pw1[i - 1], p);
		pw2[i] = mul(pw2[i - 1], inc(1, MOD - p));
	}
	for (int i = 0; i <= m; i ++)
		c[i] = mul(mul(binom(t, i), pw1[i]), pw2[t - i]);
	sc[0] = c[0];
	for (int i = 1; i <= m; i ++)
		sc[i] = inc(sc[i - 1], c[i]);
	g1[m] = g2[1] = 1;
	for (int i = 1; i <= n; i ++)
	{
		memset(h1, 0, sizeof h1);
		memset(h2, 0, sizeof h2);
		memset(ch1, 0, sizeof ch1);
		memset(ch2, 0, sizeof ch2);
		for (int j = 1; j <= m; j ++)
			h1[j] = inc(h1[j - 1], g1[j]);
		for (int j = m; j >= 1; j --)
			h2[j] = inc(h2[j + 1],  g2[j]);
//		printf("id=%d, val=%d\n", i, h1[m]); rua;
		memset(g1, 0, sizeof g1);
		memset(g2, 0, sizeof g2);
		for (int j = 1; j <= m; j ++)
			ch1[j] = inc(ch1[j - 1], mul(c[j - 1], h1[j - 1]));
		for (int j = m; j >= 1; j --)
			ch2[j] = inc(ch2[j + 1], mul(c[m - j], h2[j + 1]));
		for (int j = 1; j <= m; j ++)
		{
			g1[j] = mul(h1[m], mul(sc[j - 1], c[m - j]));
			add(g1[j], MOD - mul(ch1[j], c[m - j]));
			add(g1[j], MOD - mul(sc[j - 1], mul(c[m - j], h2[j + 1])));
			g2[j] = mul(h1[m], mul(sc[m - j], c[j - 1]));
			add(g2[j], MOD - mul(mul(c[j - 1], h1[j - 1]), sc[m - j]));
			add(g2[j], MOD - mul(ch2[j], c[j - 1]));
		}
	}
	int ans = 0;
	for (int i = 1; i <= m; i ++)
		add(ans, g1[i]);
	printf("%d\n", ans);
	return 0;
}
