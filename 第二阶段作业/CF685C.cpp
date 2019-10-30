#include <bits/stdc++.h>
#define rua system("pause")
using namespace std;
typedef long long ll;
inline ll read()
{
	ll x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
	while (isdigit(c)) {x = x * 10 + c - '0', c = getchar();}
	return x * f;
}

const int MAXN = 1e5 + 10;
const ll INF = 3e18;

int n;
ll x[MAXN], y[MAXN], z[MAXN], foo, bar, baz;

inline void Min(ll &x, ll y) {if (x > y) x = y;}
inline void Max(ll &x, ll y) {if (x < y) x = y;}

inline bool check(ll mid)
{
	static ll L[5], R[5];
	for (int i = 1; i <= 4; i ++)
		L[i] = -INF, R[i] = INF;
	for (int i = 1; i <= n; i ++)
	{
		ll A = x[i], B = y[i], C = z[i];
		Max(L[1], A + B + C - mid);
		Min(R[1], A + B + C + mid);
		Max(L[2], -A + B + C - mid);
		Min(R[2], -A + B + C + mid);
		Max(L[3], A - B + C - mid);
		Min(R[3], A - B + C + mid);
		Max(L[4], A + B - C - mid);
		Min(R[4], A + B - C + mid);
	}
	for (int i = 0; i < 2; i ++)
	{
		static ll l[5], r[5];
		for (int j = 1; j <= 4; j ++)
			l[j] = ((L[j] & 1) == i) ? L[j] : L[j] + 1,
			r[j] = ((R[j] & 1) == i) ? R[j] : R[j] - 1;
		ll low = l[2] + l[3] + l[4];
		ll high = r[2] + r[3] + r[4];
		for (int j = 1; j <= 4; j ++)
			if (l[j] > r[j]) goto finish;
		if (low > r[1] || high < l[1]) goto finish;
//		if (!mid) cerr << i << " " << l[0] << " " << r[0] << endl;
		l[1] -= low, r[1] -= low;
		if (l[1] <= 0)
		{
			foo = l[2];
			bar = l[3];
			baz = l[4];
			return 1;
		}
		for (int j = 2; j <= 4; j ++) r[j] -= l[j];
		if (l[1] <= r[2])
		{
			foo = l[2] + l[1];
			bar = l[3];
			baz = l[4];
			return 1;
		}
		l[1] -= r[2];
		if (l[1] <= r[3])
		{
			foo = l[2] + r[2];
			bar = l[3] + l[1];
			baz = l[4];
			return 1;
		}
		l[1] -= r[3];
		if (l[1] <= r[4])
		{
			foo = l[2] + r[2];
			bar = l[3] + r[3];
			baz = l[4] + l[1];
			return 1;
		}
		finish:;
	}
	return 0;
}

int main()
{
	int t = read();
	while (t --)
	{
		n = read();
		for (int i = 1; i <= n; i ++)
			x[i] = read(), y[i] = read(), z[i] = read();
		ll l = 0, r = 3e18, ans = -1;
		while (l <= r)
		{
			ll mid = (l + r) >> 1;
			if (check(mid)) r = mid - 1, ans = mid;
			else l = mid + 1;
		}
		assert(ans != -1);
		printf("%lld %lld %lld\n", (bar + baz) / 2, (foo + baz) / 2, (foo + bar) / 2);
	}

	return 0;
}
