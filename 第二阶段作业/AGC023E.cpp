#include <bits/stdc++.h>
#define rua system("pause")
using namespace std;
typedef long long ll;

#define int ll

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
inline int mul(int x, int y) {return 1LL * x * y % MOD;}
inline int qpow(int x, int y)
{
	int res = 1;
	for (; y; y >>= 1, x = mul(x, x))
		if (y & 1) res = mul(res, x);
	return res;
}

const int MAXN = 2e5 + 10;

int n, a[MAXN], zero[MAXN], pos[MAXN], D[MAXN], cnt[MAXN], S;

struct mybit
{
	int v[MAXN];
	void clear() {memset(v, 0, sizeof v);}
	mybit() {clear();}
	void add(int x, int w) {for (; x <= n; x += x & -x) ::add(v[x], w);}
	int sum(int x) {int s = 0; for (; x; x -= x & -x) ::add(s, v[x]); return s;}
	int query(int l, int r) {return sum(r) - sum(l - 1);}
} b1, b2;

signed main()
{
	n = read();
	for (int i = 1; i <= n; i ++) cnt[a[i] = read()] ++;
	for (int i = n; i >= 1; i --) cnt[i] += cnt[i + 1];
	S = 1;
	for (int i = 1; i <= n; i ++) S = mul(S, max(0LL, cnt[i] - (n - i)));
	if (!S) return puts("0"), 0;
	int blk = 0; D[0] = pos[0] = 1;
	for (int i = 1; i <= n; i ++)
	{
		D[i] = mul(cnt[i] - n + i - 1, qpow(cnt[i] - n + i, MOD - 2));
		if (!D[i]) pos[zero[i] = ++ blk] = i, D[i] = D[i - 1];
		else zero[i] = blk, D[i] = 1LL * D[i - 1] * D[i] % MOD;
	}
	int ans = 0;
	for (int i = 1; i <= n; i ++)
	{
		int now = mul(b1.query(pos[zero[a[i]]], a[i]), mul(mul(S, (MOD + 1) / 2), D[a[i]]));
		add(ans, now), b1.add(a[i], qpow(D[a[i]], MOD - 2));
	}
	b1.clear();
	for (int i = n; i >= 1; i --)
	{
		int now = b1.query(pos[zero[a[i]]], a[i] - 1);
		now = mul(now, mul(D[a[i]], mul(S, (MOD + 1) / 2)));
		now = inc(mul(S, b2.sum(a[i] - 1)), MOD - now);
		add(ans, now), b1.add(a[i], qpow(D[a[i]], MOD - 2)), b2.add(a[i], 1);
	}
	printf("%lld\n", ans % MOD);
	return 0;
}
