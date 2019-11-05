
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
 
typedef long double db;
 
const int MAXN = 1.5e5 + 10;
 
int n, p[MAXN], t[MAXN], a[MAXN]; ll l[MAXN], r[MAXN], sum[MAXN], T;
 
inline bool cmp(const int &a, const int &b) {return (ll)p[a] * t[b] > (ll)p[b] * t[a];}
 
inline bool cmp2(const int &a, const int &b) {return p[a] < p[b];}
 
inline db calc(int p, ll x, db c) {return (1.0L - c * x / T) * p;}
 
inline bool check(db mid)
{
	db now = 0;
	for (int i = 1, j = 1; i <= n; i ++)
	{
		while (j < i && p[a[j]] < p[a[i]])
		{
			now = max(now, calc(p[a[j]], l[a[j]], mid));
			j ++;
		}
		if (now >= calc(p[a[i]], r[a[i]], mid)) return 0;
	}
	return 1;
}
 
int main()
{
	n = read();
	for (int i = 1; i <= n; i ++) p[i] = read();
	for (int i = 1; i <= n; i ++) T += t[i] = read();
	for (int i = 1; i <= n; i ++) a[i] = i;
	sort(a + 1, a + 1 + n, cmp);
	l[a[1]] = 0;
	for (int i = 1; i <= n; i ++)
		sum[i] = sum[i - 1] + t[a[i]];
	for (int i = 2; i <= n; i ++)
	{
		int cur = a[i];
		if ((ll)p[cur] * t[a[i - 1]] == (ll)p[a[i - 1]] * t[cur]) l[cur] = l[a[i - 1]];
		else l[cur] = sum[i - 1];
	}
	for (int i = 1; i <= n; i ++) l[i] += t[i];
	r[a[n]] = sum[n];
	for (int i = n - 1; i >= 1; i --)
	{
		int cur = a[i];
		if ((ll)p[cur] * t[a[i + 1]] == (ll)p[a[i + 1]] * t[cur]) r[cur] = r[a[i + 1]];
		else r[cur] = sum[i];
	}
//	for (int i = 1; i <= n; i ++)
//		printf("%lld %lld\n", l[i], r[i]);
	db L = 0, R = 1;
	sort(a + 1, a + 1 + n, cmp2);
	for (int tim = 1; tim <= 50; tim ++)
	{
		db MID = (L + R) / 2;
		if (check(MID)) L = MID;
		else R = MID;
	}
	printf("%.10lf\n", (double)L);
	return 0;
}

