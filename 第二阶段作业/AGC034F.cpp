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
const int inv2 = (mod + 1) / 2;
inline int inc(int x, int y) {x += y; return x >= mod ? x - mod : x;}
inline int mul(int x, int y) {return (ll)x * y % mod;}
inline int qpow(int x, int y)
{
	int res = 1;
	for (; y; y >>= 1, x = mul(x, x))
		if (y & 1) res = mul(res, x);
	return res;
}

void fwt(int n, int *a)
{
	for (int i = 1; i < n; i <<= 1)
		for (int j = 0; j < n; j += i << 1)
			for (int k = 0; k < i; k ++)
			{
				int x = a[j + k], y = a[i + j + k];
				a[j + k] = inc(x, y);
				a[i + j + k] = inc(x, mod - y);
			}
}

void ifwt(int n, int *a)
{
	for (int i = 1; i < n; i <<= 1)
		for (int j = 0; j < n; j += i << 1)
			for (int k = 0; k < i; k ++)
			{
				int x = a[j + k], y = a[i + j + k];
				a[j + k] = mul(inc(x, y), inv2);
				a[i + j + k] = mul(inc(x, mod - y), inv2);
			}
}

const int maxn = (1 << 18) + 5;
int n, a[maxn], b[maxn], p[maxn];

int main()
{
	n = read(), n = 1 << n;
	for (int i = 0; i < n; i ++) p[i] = read();
	int s = 0;
	for (int i = 0; i < n; i ++) s = inc(s, p[i]);
	s = qpow(s, mod - 2);
	for (int i = 0; i < n; i ++) p[i] = mul(s, p[i]);
	for (int i = 0; i < n; i ++) a[i] = p[i]; a[0] = inc(a[0], mod - 1);
	for (int i = 0; i < n; i ++) b[i] = mod - 1; b[0] = inc(b[0], n);
	fwt(n, a), fwt(n, b);
	for (int i = 0; i < n; i ++) a[i] = mul(b[i], qpow(a[i], mod - 2));
	ifwt(n, a); int delta = mod - a[0];
	for (int i = 0; i < n; i ++) a[i] = inc(a[i], delta);
	for (int i = 0; i < n; i ++)
		printf("%d\n", a[i]);
	return 0;
}