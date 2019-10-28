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

const int MAXN = 20005;
const int inf = 0x3f3f3f3f;
int n, cnt1, cnt2, a[MAXN], b[MAXN], ans;
char s[MAXN], t[MAXN];

int main()
{
	n = read(), ans = inf;
	scanf("%s", s + 1);
	scanf("%s", t + 1);
	cnt1 = cnt2 = 5000;
	if (s[1] != t[1]) a[++ cnt1] = 0;
	for (int i = 1; i <= n; i ++)
		if (s[i] != s[i + 1]) a[++ cnt1] = i;
	for (int i = 1; i <= n; i ++)
		if (t[i] != t[i + 1]) b[++ cnt2] = i;
	int st1 = cnt1, st2 = cnt2;
	for (int i = 1; i <= 5000; i ++)
		a[++ cnt1] = b[++ cnt2] = n;
	while (cnt1 < cnt2) a[++ cnt1] = n;
	while (cnt2 < cnt1) b[++ cnt2] = n;
	for (int i = -st1; i <= st2; i ++) if (!(i & 1))
	{
		int now = 0;
		for (int j = 1; j <= cnt1; j ++)
		{
			int other = j + i;
			if (other >= 1 && other <= cnt1 && a[other] != b[j])
				now += abs(a[other] - b[j]);
		}
		ans = min(ans, now);
	}
	printf("%d\n", ans);
	return 0;
}
