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

const int MAXN = 3e5 + 10;
int n, a[MAXN];
ll s1[MAXN], s2[MAXN], dp[MAXN];

inline bool check(ll x)
{
	dp[0] = 0;
	for (int i = 1; i <= n; i ++)
	{
		ll now = s1[i] - s2[i];
		
		if (i & 1)
		{
			if (i != n)
			{
				dp[i] = dp[i - 1];
				if (now - dp[i - 1] >= x)
					dp[i] = min(dp[i], s1[i + 1] - s2[i + 1]);
			}
			else
			{
				if (now - dp[i - 1] >= x) return 1;
				else return 0;
			}
		}
		
		else dp[i] = dp[i - 1];
	}
	assert(0);
	return 0;
}

int main()
{
	n = read();
	for (int i = 1; i <= n; i ++) a[i] = read();
	for (int i = 1; i <= n; i ++)
	{
		s1[i] = s1[i - 1];
		s2[i] = s2[i - 1];
		if (i & 1) s1[i] += a[i];
		else s2[i] += a[i];
	}
	
	if (!(n & 1))
	{
		printf("%lld %lld\n", max(s1[n], s2[n]), min(s1[n], s2[n]));
		return 0;
	}
	
	ll ans = s2[n], L = 0, R = s1[n] + s2[n], res = 0;
	while (L <= R)
	{
		ll MID = (L + R) >> 1;
		if (check(MID)) L = MID + 1, res = MID;
		else R = MID - 1;
	}
	printf("%lld %lld\n", ans + res, s1[n] + s2[n] - ans - res);
	return 0;
}
