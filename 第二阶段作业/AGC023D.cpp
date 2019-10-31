#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	return x*f;
}
const int maxn = 1e5 + 10;
int n, s, a[maxn], pos; ll ans, p[maxn];
int dfs(int l, int r)
{
	if (r <= pos)
	{
		ans = abs(s - a[l]);
		return a[l];
	}
	else if (l > pos)
	{
		ans = abs(a[r] - s);
		return a[r];
	}
	int np;
	if (p[l] >= p[r])
	{
		p[l] += p[r], np = dfs(l, r - 1), ans += abs(a[r] - np);
		return a[r];
	}
	else
	{
		p[r] += p[l], np = dfs(l + 1, r), ans += abs(np - a[l]);
		return a[l];
	}
}
int main()
{
	n = read(), s = read();
	for (int i = 1; i <= n; i ++)
		a[i] = read(), p[i] = read();
	pos = upper_bound(a + 1, a + 1 + n, s) - a - 1;
	dfs(1, n);
	printf("%lld\n", ans);
	return 0;
}
