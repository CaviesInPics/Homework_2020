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

const int maxn = 1e5 + 10;
int n, m, k, p, h[maxn], a[maxn];
struct mypair
{
	ll first, second;
	mypair() {}
	mypair(ll x, ll y) {first = x, second = y;}
	inline bool operator < (const mypair &rhs) const {return first == rhs.first ? second < rhs.second : first > rhs.first;}
};
priority_queue< mypair > q;

inline bool check(ll mid)
{
	static ll d[maxn];
	memset(d, 0, sizeof d);
	while (q.size()) q.pop();
	for (int i = 1; i <= n; i ++)
		if ((mid - 1ll * a[i] * m) < h[i])
			q.push(mypair(mid / a[i], i));
	for (int i = 1; i <= m; i ++)
	{
		for (int j = 1; j <= k; j ++)
		{
			if (q.empty()) return 1;
			auto cur = q.top(); q.pop();
			if (cur.first < i) return 0;
			int x = cur.second;
			d[x] += p;
			if (mid + d[x] - 1ll * a[x] * m < h[x])
				q.push(mypair((mid + d[x]) / a[x], x));
		}
	}
	if (q.size()) return 0;
	else return 1;
}

int main()
{
	cin >> n >> m >> k >> p;
 	for (int i = 1; i <= n; i ++)
	 	h[i] = read(), a[i] = read();
	ll l = 0, r = 0, res = 0;
	for (int i = 1; i <= n; i ++)
		r = max(r, 1ll * a[i] * m + h[i]);
	while (l <= r)	
	{
		ll mid = (l + r) >> 1;
		if (check(mid)) r = mid - 1, res = mid;
		else l = mid + 1;
	}
	printf("%lld\n", res);
	return 0;
}